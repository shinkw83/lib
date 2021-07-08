#ifndef autoTracking_H
#define autoTracking_H

#include <iostream>
#include <cmath>

#define Rad_to_deg 57.2957951
#define H_CAMERA_DEGREE 18
#define XNP6550V_CAMERA_DEGREE 5
#define XNP6330V_CAMERA_DEGREE 9.5
#define AXIS_A6155 5.5 

#define HW_TILT_VALUE -1.0

using namespace std;

class autoTracking
{
	public:
		autoTracking();
		~autoTracking();

		double m_x_pos;
		double m_y_pos;
		double m_z_pos;
		double m_rdistance;
		double m_pan_angle;
		double m_tilt_angle;

		double m_pan_val;
		double m_tilt_val;
		double m_distance; 

		double m_cameraX;
		double m_cameraY;
		double m_cameraZ;
		double m_camera_degree;
		int    m_camera_type;

		double get_pan_value(){return m_pan_val;}
		double get_tilt_value(){return m_tilt_val;}
		double get_distance_value(){return m_distance;}

		void show_val();
		void init_camera_type(int type){ m_camera_type = type;}
		void init_camera_XYZ(double x, double y, double z){m_cameraX=x, m_cameraY=y, m_cameraZ=z;}
		void init_camera_degree(double degree) {m_camera_degree = degree;}
		
		void rect_to_polar(double x, double y,double z);
		void rotation(double x, double y,double degree);
		void auto_tracking(double x, double y, double z);
		void rotation_yaw(double yaw); // right 0> left <0  
		void calDistance(double x, double y, double z);
};
#endif 

