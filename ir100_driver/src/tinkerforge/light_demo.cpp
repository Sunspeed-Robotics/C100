#include <stdio.h>
#include <unistd.h>
#include <tinkerforge/ip_connection.h>
#include <tinkerforge/bricklet_led_strip.h>
#include <ros/ros.h>


int main(int argc,char* argv[])
{
  ros::init(argc,argv,"light_demo");
  ros::NodeHandle nh;
  ros::NodeHandle *private_nh;
  private_nh = new ros::NodeHandle("~");
  std::string host,uid;
  int port;
  private_nh->param("host",host,std::string("localhost"));
  private_nh->param("port",port,4223);
  private_nh->param("uid",uid,std::string("wWu"));

  IPConnection ipcon;
  LEDStrip ls;
  // Create IP connection
  ipcon_create(&ipcon);

  // Create device object
  led_strip_create(&ls, uid.c_str(), &ipcon);

  // Connect to brickd
  if(ipcon_connect(&ipcon, host.c_str(), port) < 0) {
    fprintf(stderr, "Could not connect\n");
  }
  // Don't use device before ipcon is connected

  led_strip_set_chip_type(&ls,2812);

  uint8_t r[16] = {0};
  uint8_t g[16] = {0};
  uint8_t b[16] = {0};// = {0};

  memset(r,0,16);//blue
  memset(g,0,16);//red
  memset(b,0,16);//green
  led_strip_set_rgb_values(&ls, 0, 16, r, g, b);//g,r,b
  led_strip_set_rgb_values(&ls, 16, 16, r, g, b);
  led_strip_set_rgb_values(&ls, 32, 16, r, g, b);
  led_strip_set_rgb_values(&ls, 48, 16, r, g, b);
  led_strip_set_rgb_values(&ls, 64, 4, r, g, b);
  led_strip_destroy(&ls);
  ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
  return 0;
}
