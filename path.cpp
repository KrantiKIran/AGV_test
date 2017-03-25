#include <iostream>
#include <vector>
#include <cmath>
#define calibre_high 30.0//lowest steering angle of car
#define calibre_low -30.0//highest steering angle of car
#define step_size_steering 5.0 //calibration of steering
#define car_length 5.0//Length of car
#define PI 3.14
#define delta_distance 10.0//distance that the car is assumed to move in one action

using namespace std;

class node
{
public:
	float x,y,th;
};

float to_rad(float deg)
{
	float tmp;
	
	tmp=fmod(deg,360);
	
	return ((tmp/180)*PI);
}

node node_child(node node_parent,float angle)
{
	node child;
	float angle_ofturn,radius,centre_x,centre_y;
	if(angle!=0)
		{
		 	angle_ofturn=delta_distance/car_length*tan(angle);//Angle by which the car moves on the circle of given radius
	 		radius=angle/angle_ofturn;//radius of curvature of car's path for the given steering angle
			centre_x=node_parent.x-sin(node_parent.th)*radius;//centre of curvature of car's path
	 		centre_y=node_parent.y+cos(node_parent.th)*radius;
			child.x = centre_x+sin(node_parent.th+angle_ofturn)*radius;//next location
			child.y = centre_y-cos(node_parent.th+angle_ofturn)*radius;
			child.th =fmod(node_parent.th+angle_ofturn,2*PI) ;
		}
	else//if the car moves straight
	{
		child.th=node_parent.th;
		child.x=node_parent.x+delta_distance*cos(node_parent.th);
		child.y=node_parent.y+delta_distance*sin(node_parent.th);
	}
	
	return child;
}

int main()
{
	float steer[(int)((calibre_high-calibre_low)/step_size_steering)+1];

	for(int i=0;i<((calibre_high-calibre_low)/step_size_steering+1);i++)
		steer[i]=to_rad(calibre_low+step_size_steering*i);

	node start;
	vector<node> children;

	cin>>start.x>>start.y>>start.th;
	start.th=to_rad(start.th);

	for(int i=0;i<((calibre_high-calibre_low)/step_size_steering+1);i++)
	{
		children.push_back(node_child(start,steer[i]));
	}

	for(int i=0;i<((calibre_high-calibre_low)/step_size_steering+1);i++)
		cout <<"x "<<children[i].x<<" y  "<<children[i].y<<" th  "<<children[i].th/PI*180<<endl;

	return 0;
}

