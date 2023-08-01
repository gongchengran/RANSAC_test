#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "Please provide input point cloud data." << std::endl;
    return -1;
  }

  // 读取点云数据
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud) == -1)
  {
    std::cerr << "Failed to read input point cloud data file." << std::endl;
    return -1;
  }

  // 创建分割对象
  pcl::SACSegmentation<pcl::PointXYZ> seg;
  // 设置分割对象的参数
  seg.setOptimizeCoefficients(true);
  seg.setModelType(pcl::SACMODEL_PLANE);
  seg.setMethodType(pcl::SAC_RANSAC);
  seg.setMaxIterations(1000);
  seg.setDistanceThreshold(0.01);

  // 创建模型参数对象
  pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
  // 创建点索引对象
  pcl::PointIndices::Ptr inliers(new pcl::PointIndices);

  // 执行RANSAC算法
  seg.setInputCloud(cloud);
  seg.segment(*inliers, *coefficients);

  // 输出模型参数
  std::cout << "Model coefficients: " << coefficients->values[0] << " "
                                      << coefficients->values[1] << " "
                                      << coefficients->values[2] << " "
                                      << coefficients->values[3] << std::endl;

  // 输出内点个数
  std::cout << "Inliers: " << inliers->indices.size() << std::endl;

  // 保存分割结果到pcd文件
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::ExtractIndices<pcl::PointXYZ> extract;
  extract.setInputCloud(cloud);
  extract.setIndices(inliers);
  extract.setNegative(false);
  extract.filter(*cloud_filtered);
  pcl::PCDWriter writer;
  writer.write<pcl::PointXYZ>("../output.pcd", *cloud_filtered, false);

  return 0;
}