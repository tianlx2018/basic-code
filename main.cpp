
#include "stdio.h"

class CBox
{
public:
  CBox(void);
  CBox(float length,float width,float height);
  float GetVolume(void);
  float GetArea(void);
  void SetPara(float length,float width,float height);
private:
  float b_length;
  float b_width;
  float b_height;
};

CBox::CBox(void)
{
  b_height = 1;
  b_length = 1;
  b_width = 1;
}

CBox::CBox(float length,float width,float height)
{
  b_height = height;
  b_length = length;
  b_width = width;
}

void CBox::SetPara(float length,float width,float height)
{
  b_height = height;
  b_length = length;
  b_width = width;
}

float CBox::GetVolume(void)
{
  return b_height*b_length*b_width;
}

float CBox::GetArea(void)
{
  return 2*(b_height*b_length + b_length*b_width +b_width*b_height);
}


class cAnimal
{
public:
  cAnimal(void)
  {
    age = 1;
  }
  
  cAnimal(int value)
  {
    age = value;
  }
  
  virtual void hoo(void)
  {
    printf("\n animal hoo");
  }
  
  void age_set(int value)
  {
    age = value;
  }
  
  int age_get(void)
  {
    return age;
  }
  
private:
  int age;
};

class cCat:public cAnimal
{
public:
  cCat(void)
  {
  }
  
  cCat(int age):cAnimal(age)
  {
  }
  
  void hoo(void)
  {
    printf("\n cat meow");
  }
};


class cBear:public cAnimal
{
public:
  cBear()
  {
  }
  
  cBear(int age):cAnimal(age)
  {   
  }
  
  void hoo(void)
  {
    printf("\n bear haa");
  }
};


class cPanda:public cCat,public cBear
{
public:
  cPanda()
  {
   weight = 10;
   gendor = 1;
  }
  
  cPanda(int weight,int gendor,int age):cCat(age),cBear(age)
  {
    weight = weight;
    gendor = gendor;
  }
  
  void hoo(void)
  {
    printf("\n panda speeking ");
  }
  
  void weight_set(int value)
  {
    weight = value;
  }
  
  void gendor_set(int value)
  {
    gendor = value;
  }  
  
  int weight_get(void)
  {
    return weight;
  }	
  
  int gendor_get(void)
  {
    return gendor;
  } 
  
private:
  int weight;
  int gendor;
};



//class cStudent
//{
//public:
//void cStudent(string name,string native,int id,int age,int score);
//void cStudent(const cStudent &c);
//{
//	
//}
//void display(void);
//private:
//	char name[10];
//	char native[10];
//	int id;
//	int age;
//	int score;
//protected:
//};
//
//cStudent::cStudent(char *p_name,char *p_native,int id,int age,int score)
//{
//	name = name;
//	native = native;
//	id = id;
//	age = age;
//	score = score;
//}
//
//cStudent::display()
//{
//	printf("\n name %s",name);
//	
//}

#include <string>
#include <iostream>
int main()
{
  string s1 = "hello";
  string s2 = "tianlx";
  string s = s1+s2;
  
  cout<<s<<endl;
  
  //CBox my_box(3,4,5);
  
  //  CBox my_box;
  //  
  //  printf("volume:%f\n",my_box.GetVolume());
  //  printf("area:%f\n",my_box.GetArea());
  //  
  //  my_box.SetPara(4,5,6);
  //  printf("volume:%f\n",my_box.GetVolume());
  //  printf("area:%f\n",my_box.GetArea());  

  cAnimal Animal;
  
  Animal.age_set(10);
  Animal.hoo();
  printf("\n animal age %d",Animal.age_get());
  
  cCat cat(12);
  
  cat.hoo();
  printf("\n cat age %d",cat.age_get());
  
  
  cCat *p2;
  cPanda panda;
  p2 = &panda;
  
  panda.hoo();
  printf("\n panda weight %d",panda.weight_get());
  printf("\n panda age %d",p2->age_get());
  printf("\n panda gendor %d",panda.gendor_get());
  return 0;
}




/*******************************************************************************
* 功能描述：
* 输入参数：
* 输出参数：
* 返回值：
* 其它说明：
* 修改记录：   
********************************************************************************/
