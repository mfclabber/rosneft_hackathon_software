#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/msg/grid_map.hpp>
#include <grid_map_core/grid_map_core.hpp>

class SurfaceMapNode : public rclcpp::Node
{
public:
    SurfaceMapNode()
        : Node("surface_map_node"), map_({"elevation"})
    {
        // Параметры
        pointcloud_topic_ = this->declare_parameter<std::string>("pointcloud_topic", "/camera/camera/depth/color/points");
        frame_id_ = this->declare_parameter<std::string>("frame_id", "map");

        // Подписчик
        pointcloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            pointcloud_topic_, 10, std::bind(&SurfaceMapNode::pointCloudCallback, this, std::placeholders::_1));

        // Публикация карты
        grid_map_pub_ = this->create_publisher<grid_map_msgs::msg::GridMap>("/surface_map", 10);

        // Инициализация карты
        map_.setFrameId(frame_id_);
        map_.setGeometry(grid_map::Length(20.0, 20.0), 0.1); // 20x20 метров с разрешением 0.1 м
    }

private:
    void pointCloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        // Обнуляем слой elevation
        map_["elevation"].setConstant(NAN);

        // Итераторы облака точек
        sensor_msgs::PointCloud2ConstIterator<float> iter_x(*msg, "x");
        sensor_msgs::PointCloud2ConstIterator<float> iter_y(*msg, "y");
        sensor_msgs::PointCloud2ConstIterator<float> iter_z(*msg, "z");

        for (; iter_x != iter_x.end(); ++iter_x, ++iter_y, ++iter_z)
        {
            float x = *iter_x;
            float y = *iter_y;
            float z = *iter_z;

            // Проверяем валидность координат
            if (std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && z > 0.0)
            {
                grid_map::Position position(x, y);

                // Проверяем, внутри ли точки
                if (map_.isInside(position))
                {
                    // Устанавливаем значение высоты
                    map_.atPosition("elevation", position) = z;
                }
            }
        }

        // Публикуем карту
        auto message = grid_map::GridMapRosConverter::toMessage(map_);
        grid_map_pub_->publish(*message);
        RCLCPP_INFO(this->get_logger(), "Published surface map.");
    }


    // Параметры
    std::string pointcloud_topic_;
    std::string frame_id_;

    // Подписчик и публикация
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_sub_;
    rclcpp::Publisher<grid_map_msgs::msg::GridMap>::SharedPtr grid_map_pub_;

    // Карта
    grid_map::GridMap map_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SurfaceMapNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
