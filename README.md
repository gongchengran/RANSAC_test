# RANSAC_test
Ransac plane fitting test  
# Build  
cd RANSAC_test  
mkdir build  
cd build  
make  
./RANSAC_TEST ../lidar_ins_odom.pcd  
# Description
It can be seen from the figure that there are some differences between the two point cloud sequences in the Z direction.  
![image-2](https://github.com/gongchengran/RANSAC_test/assets/119594722/a6383485-b70a-4dce-81d3-9d586f5dc0e5)  
When the threshold is set to 0.01, that is, 1cm, the pcd point cloud map is obtained by plane fitting as shown below.  
![image-3](https://github.com/gongchengran/RANSAC_test/assets/119594722/e7620cd1-8051-4b7f-b8ba-35bcc6c36b07)
Seeing that the trajectory is missing, the distance exceeds the threshold because the vehicle is shaking during the movement, and the test is carried out again when the threshold is set to 0.1, that is, 10cm.  
![image-4](https://github.com/gongchengran/RANSAC_test/assets/119594722/2d2b4811-09d6-454d-bf38-3c56779db4e5)
See the relaxed threshold fitting to get the complete plane.  
