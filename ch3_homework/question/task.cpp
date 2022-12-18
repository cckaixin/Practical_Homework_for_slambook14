
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

int main(int argc, char const *argv[])
{
//hint 1: Find the Euler Angle from Frame1 to Frame2

//hint 2: Convert the Euler Angle into the rotation matrix

//hint 3: Try to convert a known point under the Frame1, like (1,1,1), to Frame2 using the rotation matrix, 
//        and then you can check if your answer is correct intuitively. (The answer is (1, -1, -1))

    return 0;
}
