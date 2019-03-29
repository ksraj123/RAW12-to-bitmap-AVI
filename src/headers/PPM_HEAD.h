#ifndef PPM_HEAD
#define PPM_HEAD

#include "functional.h"

namespace OutputImage {

namespace pixelmap{

    void write_channel(std::ofstream*, uint8_t arr[max_height+1][max_width+1], std::string);
}
}
#endif
