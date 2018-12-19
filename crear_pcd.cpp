#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
//Necesario: Libreria PCL
//sudo add-apt-repository ppa:v-launchpad-jochen-sprickerhof-de/pcl
//sudo apt-get update
//Para ver objetos 3d con .obj https://poly.google.com/uploads
//https://larrylisky.com/2016/11/03/point-cloud-library-on-ubuntu-16-04-lts/ para pcl

// https://larrylisky.com/2014/03/03/installing-pcl-on-ubuntu/
//https://askubuntu.com/questions/761127/how-do-i-install-openjdk-7-on-ubuntu-16-04-or-higher
//sudo apt install libpcl-dev
//sudo apt-get install libpcl-all
//sudo apt-get install libpcl1

//Ejecutar obj2pcd-master : cmake . -> make -> ./obj2pcd objeto.obj -> objeto.pcd

using namespace std;

int main(int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ> cloud;
  pcl::io::loadPCDFile("objecto.obj", cloud_blob);

  //Fill in the cloud data
  cloud.width = 15704;
  cloud.height = 1;
  cloud.is_dense = false;
  cloud.points.resize(cloud.width * cloud.height);

  for(size_t i=0; i< cloud.points.size(); ++i)
  {
    cloud.points[i].x;
    cloud.points[i].y;
    cloud.points[i].z;
  }

  pcl::io::savePCDFileASCII("objeto.pcd",cloud);
  std::cerr<<"Saved "<< cloud.points.size()<< "data points to taza.pcd."<<std::endl;

  for(size_t i=0; i<cloud.points.size();++i)
    std::cerr<<" "<<cloud.points[i].x<<" "<<cloud.points[i].y<<" "<<cloud.points[i].z<<std::endl;
  return(0);

}
