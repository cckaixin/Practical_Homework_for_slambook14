
/**************************************************QUESTION***********************************************/
//有两个右手系1和2,其中2系的x轴与1系的y轴方向相同，2系的y轴与1系z轴方向相反，2系的z轴与1系的x轴相反,两个坐标系原点重合
//求R12，求1系中(1,1,1)在2系中的坐标。请自己编写一个c++程序实现它，并用Cmake编译，得到能输出答案的可执行文件
//@ author: 全日制学生混(bilibili)
//@ homePage: https://space.bilibili.com/336103007
//@ github: https://github.com/cckaixin/Practical_Homework_for_slambook14
/*********************************************************************************************************/

#include<iostream>
#include<Eigen/Core>
#include<Eigen/Geometry>
#define PI 3.14159265358979323846

Eigen::Matrix3d RPY2Rotation(double, double, double);

int main(int argc, char const *argv[])
{
//hint 1: Find the Euler Angle from Frame1 to Frame2
    //adopt: XYZ rotation order(i.e. roll-pitch-yaw, and ACTIVE axis as reference),
    //eazy to see, Frame 1 ---[roll=-pi/2, pitch=-pi/2, yaw=0]---> Frame 2
    double roll,pitch,yaw;
    roll = -PI/2;
    pitch = -PI/2;
    yaw = 0;

//hint 2: Convert the Euler Angle into the rotation matrix
    Eigen::Matrix3d roation_matrix;
    // The total rotation is decomposed into three rotations about the axis
    // and then translates to the rotation matrix via AngleAxis
    Eigen::AngleAxisd rv_roll(roll, Eigen::Vector3d::UnitX());                  //ACTIVE axis
    Eigen::AngleAxisd rv_pitch(pitch, rv_roll*Eigen::Vector3d::UnitY());        //ACTIVE axis
    Eigen::AngleAxisd rv_yaw(yaw, rv_pitch*rv_roll*Eigen::Vector3d::UnitZ());   //ACTIVE axis
    
    //we choose rpy order, so total_roate = y*p*r (Beginners may get confused)
    roation_matrix = (rv_yaw*rv_pitch*rv_roll).toRotationMatrix();    // R12

//hint 3: Try to convert a known point under the Frame1, like (1,1,1), to Frame2 using the rotation matrix, 
//        and then you can check if your answer is correct intuitively. (The answer is (1, -1, -1))
    Eigen::Vector3d point_frame1(1,1,1);
    Eigen::Vector3d point_frame2;
    point_frame2 = roation_matrix.transpose() * point_frame1;  //p2 = R21 * p1

    std::cout << "***************************************" << std::endl;
    std::cout << "point in frame1: " << point_frame1.transpose() << std::endl;
    std::cout << "point in frame2: " << point_frame2.transpose() << std::endl;
    std::cout << "R12: " << std::endl;
    std::cout << roation_matrix<< std::endl;
    std::cout << "***************************************" << std::endl;
    std::cout << std::endl;

// /*******************we can also use Fixed axis to solve******************/
//     //adopt: XYZ rotation order(i.e. roll-pitch-yaw, and FIXED axis as reference)
//     //eazy to see, Frame 1 ---[roll=-pi/2, pitch=0, yaw=pi/2]---> Frame 2
//     // or you can still use angldeAxis
//     Eigen::AngleAxisd rv_roll(-PI/2, Eigen::Vector3d::UnitX()); // FIXED axis
//     Eigen::AngleAxisd rv_pitch(0, Eigen::Vector3d::UnitY());    // FIXED axis
//     Eigen::AngleAxisd rv_yaw(PI/2, Eigen::Vector3d::UnitZ());   // FIXED axis
//     roation_matrix = (rv_yaw*rv_pitch*rv_roll).toRotationMatrix();    // R12
//     roation_matrix = RPY2Rotation(-PI/2,0,PI/2);   // FIXED axis   R12

    return 0;
}


// except for angleAxis, we can also get the rotation matrix directly from Euler angles
Eigen::Matrix3d RPY2Rotation(double roll , double pitch , double yaw)		//roll , pitch , yaw
{
	///send EulerAngles and transform into RotationMatrix 

	Eigen::Matrix3d R, Rx, Ry, Rz;

	Rx << 1.0, 0.0, 0.0,
		0.0, cos(roll), -sin(roll),
		0.0, sin(roll), cos(roll);

	Ry << cos(pitch), 0.0, sin(pitch),
		0.0, 1.0, 0.0,
		-sin(pitch), 0.0, cos(pitch);

	Rz << cos(yaw), -sin(yaw), 0.0,
		sin(yaw), cos(yaw), 0.0,
		0.0, 0.0, 1.0;

	R = Rz * Ry * Rx;

	return R;
}

// 你可能会疑惑，为什么把1系转到2系得到的旋转量是R12，按照我们说的从右往左读的习惯，我们应该写成R21啊？
// 我们所说的a1=R12a2+t12中，R12和t12确实是从右向左读没错，但这只是坐标变换时的较为合适的读法
// R12实际对应的是坐标系1姿态到坐标系2姿态的旋转，我们之所以说R12角标从右往左读，那是对于坐标变化来说的，对坐标轴的姿态变换要从左往右读才是真实旋转方向，这点很重要！
// 同理，t12实际对应的是坐标系1原点指向坐标系2原点的向量，我们之所以说t12角标从右往左读，那是对于坐标变换来说的，对坐标轴的位置变换要从左往右读才是真实平移向量方向，这点很重要！
