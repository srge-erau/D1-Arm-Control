#include <unitree/robot/channel/channel_publisher.hpp>
#include <unitree/common/time/time_tool.hpp>
#include "msg/ArmString_.hpp"


#define TOPIC "rt/arm_Command"

using namespace unitree::robot;
using namespace unitree::common;

int main(int argc, char* argv[])
{
    ChannelFactory::Instance()->Init(0);
    ChannelPublisher<unitree_arm::msg::dds_::ArmString_> publisher(TOPIC);
    publisher.InitChannel();

    unitree_arm::msg::dds_::ArmString_ msg{};

    std::vector<float> angles(7); // Modify these values as needed

    // Read angles starting from 3rd argument (index 2)
    for(int i = 0; i < 7; i++)
    {
        angles[i] = std::stof(argv[i + 2]);
    }

    
    std::string json_msg = "{\"seq\":4,\"address\":1,\"funcode\":2,\"data\":{\"mode\":1";

    // Add angles from vector
    for(int i = 0; i < 7; i++)
    {
    json_msg += ",\"angle" + std::to_string(i) + "\":" + std::to_string(angles[i]);
    }

    json_msg += "}}";
    std::cout << "Command sent: " << json_msg << std::endl;
    msg.data_() = json_msg;
    publisher.Write(msg);
 
    return 0;
}
