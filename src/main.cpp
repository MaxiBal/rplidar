#include <iostream>

#include "sl_lidar.h" 


using namespace sl;

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

#define LIDAR_PORT "/dev/ttyUSB0"
#define BUF_SIZE 8192

int main(void)
{
    ///  Create a communication channel instance
    auto channel = createSerialPortChannel(LIDAR_PORT, 115200); // 115200=baudrate

    std::cout << "Created channel instance.\n"; 

    ///  Create a LIDAR driver instance
    ILidarDriver* lidar = * createLidarDriver();

    std::cout << "Created lidar driver instance.\n"; 
    std::cout << "Connecting with lidar...\n";

    // connect lidar driver to channel
    auto res = lidar->connect(*channel);

    if(SL_IS_OK(res)){

        std::cout << "Connected with LIDAR at " << LIDAR_PORT << "\n\n";

        // ensure that connection to lidar works

        sl_lidar_response_device_info_t deviceInfo;
        res = lidar->getDeviceInfo(deviceInfo);

        if(SL_IS_OK(res)){

            // lidar has connected
            // print details about the lidar

            std::cout << "----------------------------\n";
            std::cout << "Starting LIDAR application...\n";
            printf("Model: %d, Firmware Version: %d.%d, Hardware Version: %d\n",
            deviceInfo.model,
            deviceInfo.firmware_version >> 8, deviceInfo.firmware_version & 0xffu,
            deviceInfo.hardware_version);
            std::cout << "----------------------------\n\n";

            // start scanning
            lidar->startScan(false, true);

            sl_lidar_response_measurement_node_hq_t nodes[BUF_SIZE];
            size_t  count = _countof(nodes);

            res = lidar->grabScanDataHq(nodes, count);

            if (SL_IS_OK(res))
            {
                // print out all scan_data
                for (int pos = 0; pos < (int)count ; ++pos) {
                    printf("%s theta: %03.2f Dist: %08.2f Q: %d \n", 
                        (nodes[pos].flag & SL_LIDAR_RESP_HQ_FLAG_SYNCBIT) ?"S ":"  ", 
                        (nodes[pos].angle_z_q14 * 90.f) / 16384.f,
                        nodes[pos].dist_mm_q2/4.0f,
                        nodes[pos].quality >> SL_LIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
                }
            }
            else
            {
                fprintf(stderr, "Failed to get scan data from LIDAR %08x\r\n", res);
            }

        }
        else{
            fprintf(stderr, "Failed to get device information from LIDAR %08x\r\n", res);
        }
    }else{
        fprintf(stderr, "Failed to connect to LIDAR %08x\r\n", res);
    }
	
    /// Delete Lidar Driver and channel Instance
    delete lidar;
}
