/**
*���ܣ��Զ���ֵ����
*
*/
#include "common.h"
#include "include.h"
#define N 5000                  //Ҫ������ĸ���
#define RISE 50                 //�����׶ε���
#define TREND 10

struct wave
{
  int rize;
  int down;
  int offset;
}pid;
struct wave pid=
{
  .rize = 0,
  .down = 0,
  .offset = 10                              //��������ֵ
};
  
//PID����
//���²���������ֵ��10%��������Ҫ��ʱ�Ż�����
//������Ҫ��ĵ�ĸ���С���ܵ�����10%Ϊ����
//return �� 0Ϊ����Ҫ��1Ϊ�д��Ľ�
int PID(float *p ,float *i ,float *d ,float value)
{
  *i = *d = 0;
  
  static int count[4]={0};                 //��־������Ҫ��ĵ�ĸ�������ǰ�ĵ���,,��1��2��������,
//  static int 
  static float history[2] = {0};                //����ֵ����ʷ��������ʷ
  int edited_p=0,edited_i=0,edited_d=0;
  if(count[1] > RISE)
  {
    if(count[1]<N)
    {
      if(value < history[0] * 1.1 && value > history[0] * 0.9)            //20%�Ĳ���
      {;}
      else                                                              //�����һ���½���
      {
        if(history[0] > value)
        {
          if(!count[2])
            count[3] = 2;
          count[2] ++;
          if(count[2] > TREND)
          {
            pid.down ++;
            count[2] = 0;
          }
        }
        else if(history[0] < value + pid.offset)
        {
          if(!count[2])
            count[3] = 1;
          count[2] ++;
          if(count[2] > TREND)
          {
            
            count[2] = 0;
          }
        }
        count[0] ++;
      }
      
      if(history[1] == count[3])
      {
        ;//��д
      }
      else
      {
        switch(count[3])
        {
          case 1:pid.rize ++;break;
          case 2:pid.down ++;break;
          default:;;
        }
        history[1] = count[3];
      }
      count[1] ++;
    }
    else                                        //����������
    {
      pid.rize = 0;
      pid.down = 0;
      count[2] = 0;
      if(count[0] > N * 0.1)
        return 0;
    }
  }
  else
  {
    pid.rize = 0;
    pid.down = 0;
    count[2] = 0;
    count[1] ++;
  }
  
  /**
  *     ����֮��鿴rize down��ֵ
  */
  if(!*i)
  {
    if(pid.rize < 3)
    {
      *p = *p + 0.01;
      if(pid.rize >= 4)
      {
          *p *= 0.75;                             //0.75ȡpֵ
          edited_p = 1;
      }
    }
    else
    {
      *p = *p - 0.01;
      if(pid.rize <6)
      {
          *p *= 0.75;                             //0.75ȡpֵ
          edited_p = 1;
      } 
    }
  }
  else if(edited_p && !edited_i)
  {
    if(pid.rize < 3)
    {
      *i = *i + 0.01;
      if(pid.rize >= 4)
      {
          *i *= 1.3;                             //0.75ȡpֵ
          edited_i = 1;
      }
    }
    else
    {
      *i = *i - 0.01;
      if(pid.rize < 6)
      {
          *i *= 1.3;                             //0.75ȡpֵ
          edited_i = 1;
      } 
    }
  }
  else if(edited_i && !edited_d)
  {
    if(pid.rize < 3)
    {
      *d = *d + 0.01;
      if(pid.rize >= 4)
      {
          *d *= 0.4;                             //0.75ȡpֵ
          edited_d = 1;
      }
    }
    else
    {
      *d = *d - 0.01;
      if(pid.rize < 6)
      {
          *d *= 1.3;                             //0.75ȡpֵ
          edited_d = 1;
      } 
    }
  }
  
  history[0] = value;
  return 1;
}