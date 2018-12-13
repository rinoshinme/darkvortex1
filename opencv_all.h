#ifndef DARKVORTEX_OPENCV_ALL_H
#define DARKVORTEX_OPENCV_ALL_H

#ifdef OPENCV
#include "opencv2/opencv.hpp"

#ifdef _WIN32
/* opencv library for windows systems */
#ifdef _DEBUG
#pragma comment(lib, "opencv_world310d.lib")
#else
#pragma comment(lib, "opencv_world310.lib")
#endif /* _DEBUG */

#else
/* opencv library for unix systems */

#endif /* _WIN32 */
#endif /* OPENCV */

#endif /* DARKVORTEX_OPENCV_ALL_H */
