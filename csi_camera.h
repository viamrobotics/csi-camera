#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <viam/sdk/components/camera/camera.hpp>
#include <viam/api/component/camera/v1/camera.grpc.pb.h>

using namespace viam::sdk;

class CSICamera : public Camera {
private:
    // Module
    std::string name;

    // Camera
    bool debug;
    int width_px = 0;
    int height_px = 0;
    int frame_rate = 0;
    std::string video_path;

    // GST
    GstElement *pipeline = nullptr;
    GstBus *bus = nullptr;
    GstMessage *msg = nullptr;
    GstSample *sample = nullptr;
    GstBuffer *buffer = nullptr;
    GstElement* appsink = nullptr;

public:
    // Constructors
    explicit CSICamera(std::string name, AttributeMap attrs);
    ~CSICamera();
    void init(AttributeMap attrs);
    void init_csi(std::string pipeline_args);
    void validate_attrs(AttributeMap attrs);

    // Camera Overrides
    // defines camera component interface
    void reconfigure(Dependencies deps, ResourceConfig cfg) override;
    raw_image get_image(std::string mime_type) override;
    // API dynamic_api() const override;
    AttributeMap do_command(AttributeMap command) override;
    point_cloud get_point_cloud(std::string mime_type) override;
    std::vector<GeometryConfig> get_geometries() override;
    properties get_properties() override;

    // GST 
    // helpers to manage GStreamer pipeline lifecycle
    std::string create_pipeline();
    void wait_pipeline();
    void stop_pipeline();
    void catch_pipeline();

    // Image 
    // helpers to pull images from appsink
    std::vector<unsigned char> get_csi_image();
    std::vector<unsigned char> buff_to_vec(GstBuffer *buff);
    std::vector<unsigned char> get_test_image();

    // Getters
    std::string get_name() const;
    bool is_debug() const;
    int get_width_px() const;
    int get_height_px() const;
    int get_frame_rate() const;
    std::string get_video_path() const;
    GstBus* get_bus() const;
    GstElement* get_appsink() const;
    GstElement* get_pipeline() const;
};
