#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

#include "constraints.h"
#include "csi_camera.h"

using namespace viam::sdk;

CSICamera::CSICamera(const std::string name, const AttributeMap attrs) : Camera(std::move(name)) {
    std::cout << "Creating CSICamera with name: " << name << std::endl;
    init(attrs);
}


CSICamera::~CSICamera() {
    std::cout << "Destroying CSICamera" << std::endl;
    stop_pipeline();
}

void CSICamera::init(const AttributeMap attrs) {
    validate_attrs(attrs);
    std::string pipeline_args = create_pipeline();
    if (debug) {
        std::cout << "pipeline_args: " << pipeline_args << std::endl;
    }
    init_csi(pipeline_args);

    return;
}

void CSICamera::validate_attrs(const AttributeMap attrs) {
    if (attrs->count("width_px") == 1) {
        std::shared_ptr<ProtoType> width_proto = attrs->at("width_px");
        auto width_value = width_proto->proto_value();
        if (width_value.has_number_value()) {
            int width_num = static_cast<int>(width_value.number_value());
            width_px = width_num;
        }
    }
    if (!width_px) {
        std::cout << "Setting width_px to default value: " << DEFAULT_INPUT_WIDTH << std::endl;
        width_px = DEFAULT_INPUT_WIDTH;
    }

    if (attrs->count("height_px") == 1) {
        std::shared_ptr<ProtoType> height_proto = attrs->at("height_px");
        auto height_value = height_proto->proto_value();
        if (height_value.has_number_value()) {
            int height_num = static_cast<int>(height_value.number_value());
            height_px = height_num;
        }
    }
    if (!height_px) {
        std::cout << "Setting height_px to default value: " << DEFAULT_INPUT_HEIGHT << std::endl;
        height_px = DEFAULT_INPUT_HEIGHT;
    }
    
    if (attrs->count("frame_rate") == 1) {
        std::shared_ptr<ProtoType> frame_proto = attrs->at("frame_rate");
        auto frame_value = frame_proto->proto_value();
        if (frame_value.has_number_value()) {
            int frame_num = static_cast<int>(frame_value.number_value());
            frame_rate = frame_num;
        }
    }
    if (!frame_rate) {
        std::cout << "Setting frame_rate to default value: " << DEFAULT_INPUT_FRAMERATE << std::endl;
        frame_rate = DEFAULT_INPUT_FRAMERATE;
    }
    
    if (attrs->count("video_path") == 1) {
        std::shared_ptr<ProtoType> video_proto = attrs->at("video_path");
        auto video_value = video_proto->proto_value();
        if (video_value.has_string_value()) {
            std::string video_str = video_value.string_value();
            video_path = video_str;
        }
    }
    if (video_path.empty() ) {
        std::cout << "Setting video_path to default value: " << DEFAULT_INPUT_SENSOR << std::endl;
        video_path = DEFAULT_INPUT_SENSOR;
    }

    if (attrs->count("debug") == 1) {
        std::shared_ptr<ProtoType> debug_proto = attrs->at("debug");
        auto debug_value = debug_proto->proto_value();
        if (debug_value.has_bool_value()) {
            bool debug_bool = static_cast<bool>(debug_value.bool_value());
            debug = debug_bool;
        }
    }

    return;
}

void CSICamera::reconfigure(const Dependencies deps, const ResourceConfig cfg) {
    if (debug) {
        std::cout << "Reconfiguring CSI Camera module" << std::endl;
    }
    stop_pipeline();
    auto attrs = cfg.attributes();
    init(attrs);

    return;
}

Camera::raw_image CSICamera::get_image(const std::string mime_type) {
    if (debug) {
        std::cout << "hit get_image. expecting mime_type " << mime_type << std::endl;
    }
    raw_image image;
    image.mime_type = DEFAULT_OUTPUT_MIMETYPE;
    if (FAKE_CAMERA) {
        image.bytes = get_test_image();
    } else {
        image.bytes = get_csi_image();
        if (image.bytes.empty()) {
            std::cerr << "ERROR: no bytes retrieved" << std::endl;
        }
    }

    return image;
}

AttributeMap CSICamera::do_command(const AttributeMap command) {
    std::cerr << "do_command not implemented" << std::endl;
    return 0;
}

Camera::point_cloud CSICamera::get_point_cloud(const std::string mime_type) {
    std::cerr << "get_point_cloud not implemented" << std::endl;
    return point_cloud{};
}

std::vector<GeometryConfig> CSICamera::get_geometries() {
    std::cerr << "get_geometries not implemented" << std::endl;
    return std::vector<GeometryConfig>{};
}

Camera::properties CSICamera::get_properties() {
    std::cerr << "get_properties not implemented" << std::endl;
    return properties{};
}

void CSICamera::init_csi(const std::string pipeline_args) {
    // Build gst pipeline
    pipeline = gst_parse_launch(
        pipeline_args.c_str(),
        nullptr
    );
    if (!pipeline) {
        std::cerr << "Failed to create the pipeline" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Print pipeline structure
    if (debug) {
        GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline_structure");
    }
    
    // Fetch the appsink element
    appsink = gst_bin_get_by_name(GST_BIN(pipeline), "appsink0");
    if (!appsink) {
        std::cerr << "Failed to get the appsink element" << std::endl;
        gst_object_unref(pipeline);
        std::exit(EXIT_FAILURE);
    }

    // Start the pipeline
    if (gst_element_set_state(pipeline, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
        std::cerr << "Failed to start the pipeline" << std::endl;
        gst_object_unref(appsink);
        gst_object_unref(pipeline);
        std::exit(EXIT_FAILURE);
    }

    // Handle async pipeline creation
    wait_pipeline();

    // Run the main loop
    bus = gst_element_get_bus(pipeline);
    if (!bus) {
        std::cerr << "Failed to get the bus for the pipeline" << std::endl;
        gst_object_unref(appsink);
        gst_object_unref(pipeline);
        std::exit(EXIT_FAILURE);
    }

    return;
}

// Handles async GST state change
void CSICamera::wait_pipeline() {
    GstState state, pending;
    GstStateChangeReturn ret;
    while ((ret = gst_element_get_state(pipeline, &state, &pending, GST_CLOCK_TIME_NONE)) == GST_STATE_CHANGE_ASYNC) {
        // wait for state change to complete
    }

    if (ret == GST_STATE_CHANGE_SUCCESS) {
        std::cout << "GST pipeline state change success" << std::endl;
    } else if (ret == GST_STATE_CHANGE_FAILURE) {
        std::cerr << "GST pipeline failed to change state" << std::endl;
        std::exit(EXIT_FAILURE);
    } else if (ret = GST_STATE_CHANGE_NO_PREROLL) {
        std::cout << "GST pipeline changed but not enough data for preroll" << std::endl;
    } else {
        std::cerr << "GST pipeline failed to change state" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return;
}

void CSICamera::stop_pipeline() {
    if (debug) {
        std::cout << "Stopping GST pipeline" << std::endl;
    }

    // Stop the pipeline
    if (gst_element_set_state(pipeline, GST_STATE_NULL) == GST_STATE_CHANGE_FAILURE) {
        std::cerr << "Failed to stop the pipeline" << std::endl;
        gst_object_unref(appsink);
        gst_object_unref(pipeline);
        std::exit(EXIT_FAILURE);
    }

    // Wait for async state change
    wait_pipeline();

    // Free resources
    gst_object_unref(appsink);
    gst_object_unref(pipeline);
    gst_object_unref(bus);
    appsink = nullptr;
    pipeline = nullptr;
    bus = nullptr;

    return;
}

void CSICamera::catch_pipeline() {
    GError* error = nullptr;
    gchar* debugInfo = nullptr;

    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_ERROR:
            gst_message_parse_error(msg, &error, &debugInfo);
            std::cerr << "Error: " << error->message << std::endl;
            std::cerr << "Debug Info: " << debugInfo << std::endl;
            stop_pipeline();
            std::exit(EXIT_FAILURE);
            break;
        case GST_MESSAGE_EOS:
            std::cout << "End of stream received" << std::endl;
            stop_pipeline();
            std::exit(EXIT_SUCCESS);
            break;
        case GST_MESSAGE_WARNING:
            gst_message_parse_warning(msg, &error, &debugInfo);
            if (debug) {
                std::cout << "Warning: " << error->message << std::endl;
                std::cout << "Debug Info: " << debugInfo << std::endl;
            }
            break;
        case GST_MESSAGE_INFO:
            gst_message_parse_info(msg, &error, &debugInfo);
            if (debug) {
                std::cout << "Info: " << error->message << std::endl;
                std::cout << "Debug Info: " << debugInfo << std::endl;
            }
            break;
        default:
            // Ignore other message types
            break;
    }

    // Cleanup
    if (error != nullptr)
        g_error_free(error);
    if (debugInfo != nullptr)
        g_free(debugInfo);
}

std::vector<unsigned char> CSICamera::get_csi_image() {
    // Pull sample from appsink
    std::vector<unsigned char> vec;
    sample = gst_app_sink_pull_sample(GST_APP_SINK(appsink));
    if (sample != nullptr) {
        // Retrieve buffer from the sample
        buffer = gst_sample_get_buffer(sample);

        // Process or handle the buffer as needed
        vec = buff_to_vec(buffer);

        // Release the sample
        gst_sample_unref(sample);
    }

    // Check bus for messages
    msg = gst_bus_pop(bus);
    if (msg != nullptr) {
        catch_pipeline();
        gst_message_unref(msg);
        msg = nullptr;
    }

    return vec;
}


std::string CSICamera::create_pipeline() {
    std::ostringstream oss;

    oss << DEFAULT_INPUT_SOURCE << " sensor_id=" << video_path
        << " ! " << DEFAULT_INPUT_FORMAT
        << ",width=" << std::to_string(width_px)
        << ",height=" << std::to_string(height_px)
        << ",framerate=" << std::to_string(frame_rate)
        << "/1 ! nvvidconv flip-method=" << DEFAULT_INPUT_FLIP_METHOD
        << " ! " << DEFAULT_OUTPUT_FORMAT
        << ",width=" << std::to_string(DEFAULT_OUTPUT_WIDTH)
        << ",height=" << std::to_string(DEFAULT_OUTPUT_HEIGHT)
        << " ! " << DEFAULT_OUTPUT_ENCODER
        << " ! " << DEFAULT_OUTPUT_MIMETYPE
        << " ! appsink name=appsink0 max-buffers=1";

    return oss.str();
}


std::vector<unsigned char> CSICamera::buff_to_vec(GstBuffer *buff) {
    // Get the size of the buffer
    size_t bufferSize = gst_buffer_get_size(buff);

    // Create a vector with the same size as the buffer
    std::vector<unsigned char> vec(bufferSize);

    // Copy the buffer data to the vector
    GstMapInfo map;
    gst_buffer_map(buffer, &map, GST_MAP_READ);
    memcpy(vec.data(), map.data, bufferSize);
    gst_buffer_unmap(buffer, &map);

    return vec;
}

std::vector<unsigned char> CSICamera::get_test_image() {
    std::string test_image_path = "./etc/viam-logo.jpeg";
    
    // Create filestream
    std::ifstream file(test_image_path, std::ios::binary);
    if (!file) {
        std::cout << "ERROR: could not open file" << std::endl;
        return {};
    }

    // Read the file contents into a vector
    std::vector<unsigned char> bytes(std::istreambuf_iterator<char>(file), {});

    return bytes;
}


std::string CSICamera::get_video_path() const {
    return video_path;
}

int CSICamera::get_width_px() const {
    return width_px;
}

int CSICamera::get_height_px() const {
    return height_px;
}

int CSICamera::get_frame_rate() const {
    return frame_rate;
}

bool CSICamera::is_debug() const {
    return debug;
}

GstElement* CSICamera::get_appsink() const {
    return appsink;
}

GstElement* CSICamera::get_pipeline() const {
    return pipeline;
}

GstBus* CSICamera::get_bus() const {
    return bus;
}