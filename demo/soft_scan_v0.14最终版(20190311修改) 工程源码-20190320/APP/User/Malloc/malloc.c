/**
	******************************************************************************
	*�ļ�����malloc.c
	*  ���ܣ���̬�ڴ�����������ٶ�̬�ڴ桢��ն�̬�ڴ桢�鿴�ڴ�ʹ�������
	*  �汾��V0.14	 
	*	 ʱ�䣺2017.10.30
	*******************************************************************************
*/
#include "malloc.h"

//�ڴ��(4�ֽڶ���)
__align(4) u8 membase[MEM_MAX_SIZE];													//�ڲ�SRAM�ڴ��
//�ڴ�����
u16 memmapbase[MEM_ALLOC_TABLE_SIZE];													//�ڲ�SRAM�ڴ��MAP
//�ڴ�������	   
const u32 memtblsize = MEM_ALLOC_TABLE_SIZE;		//�ڴ���С
const u32 memblksize = MEM_BLOCK_SIZE;					//�ڴ�ֿ��С
const u32 memsize    = MEM_MAX_SIZE;							//�ڴ��ܴ�С


//�ڴ���������
struct _m_mallco_dev mallco_dev=
{
	mem_init,				//�ڴ��ʼ��
	mem_perused,	  //�ڴ�ʹ����
	membase,		    //�ڴ��
	memmapbase,     //�ڴ����״̬��
	0,  					  //�ڴ����δ����
};
/*****************************���ϴ���Ƽ����޹�˾******************************
  * �������ƣv��mymemcpy
  * ����˵��  �������ڴ� 
  * �������  ��*des:Ŀ�ĵ�ַ
								*src:Դ��ַ               
  * �������  ���� 
  * ���ز���  ��void
*******************************************************************************/
void mymemcpy(void *des,void *src,u32 n)  
{  
  u8 *xdes=des;
	u8 *xsrc=src; 
  while(n--)*xdes++=*xsrc++;  
}  

/*****************************���ϴ���Ƽ����޹�˾******************************
  * ��������	��mymemset
  * ����˵��  �������ڴ� 
  * �������  ��*s:�ڴ��׵�ַ
                c :Ҫ���õ�ֵ
								count:��Ҫ���õ��ڴ��С(�ֽ�Ϊ��λ)
  * �������  ���� 
  * ���ز���  ��void
*******************************************************************************/
void mymemset(void *s,u8 c,u32 count)  
{  
    u8 *xs = s;  
    while(count--)*xs++=c;  
}	
/*****************************���ϴ���Ƽ����޹�˾******************************
  * ��������	��mem_init
  * ����˵��	���ڴ�����ʼ��    
  * �������  ��void 
                
  * �������  ���� 
  * ���ز���  ��void
*******************************************************************************/
void mem_init(void)  
{  
  mymemset(mallco_dev.memmap, 0,memtblsize*2);//�ڴ�״̬����������  
	mymemset(mallco_dev.membase, 0,memsize);	//�ڴ��������������  
	mallco_dev.memrdy=1;								//�ڴ�����ʼ��OK  
} 
 

/*****************************���ϴ���Ƽ����޹�˾******************************
  * ��������	��mem_perused
  * ����˵��  ����ȡ�ڴ�ʹ���� 
  * �������  ��void 
                
  * �������  ��void 
  * ���ز���  ��ʹ����(0~100)
*******************************************************************************/
u8 mem_perused(void)  
{  
    u32 used=0;  
    u32 i;  
    for(i=0;i<memtblsize;i++)  
    {  
        if(mallco_dev.memmap[i])used++; 
    } 
    return (used*100)/(memtblsize);  
}  
/*****************************���ϴ���Ƽ����޹�˾******************************
  * ��������	��mem_malloc
  * ����˵��  ���ڴ����(�ڲ�����)
  * �������  ��size->Ҫ������ڴ��С(�ֽ�) 
                
  * �������   
  * ���ز���  :0XFFFFFFFF,�������;����,�ڴ�ƫ�Ƶ�ַ 
*******************************************************************************/
u32 mem_malloc(u32 size)  
{  
    signed long offset=0;  
    u16 nmemb;	//��Ҫ���ڴ����  
		u16 cmemb=0;//�������ڴ����
    u32 i;  
    if(!mallco_dev.memrdy)mallco_dev.init();//δ��ʼ��,��ִ�г�ʼ�� 
    if(size==0)return 0XFFFFFFFF;//����Ҫ����

    nmemb=size/memblksize;  	//��ȡ��Ҫ����������ڴ����
    if(size%memblksize)nmemb++;  
    for(offset=memtblsize-1;offset>=0;offset--)//���������ڴ������  
    {     
		if(!mallco_dev.memmap[offset])cmemb++;//�������ڴ��������
		else cmemb=0;								//�����ڴ������
		if(cmemb==nmemb)							//�ҵ�������nmemb�����ڴ��
		{
            for(i=0;i<nmemb;i++)  					//��ע�ڴ��ǿ� 
            {  
                mallco_dev.memmap[offset+i]=nmemb;  
            }  
            return (offset*memblksize);//����ƫ�Ƶ�ַ  
		}
    }  
    return 0XFFFFFFFF;//δ�ҵ����Ϸ����������ڴ��  
}  

/*****************************���ϴ���Ƽ����޹�˾******************************
  * ��������	:mem_myfree 
  * ����˵��  :�ͷ��ڴ�(�ڲ�����)	
  * �������  :offset�ڴ��ַƫ�� 
                
  * �������  : 
  * ���ز���  :0,�ͷųɹ�;1,�ͷ�ʧ��; 
*******************************************************************************/
u8 mem_myfree(u32 offset)  
{  
    int i;  
    if(!mallco_dev.memrdy)//δ��ʼ��,��ִ�г�ʼ��
	{
		mallco_dev.init();    
        return 1;//δ��ʼ��  
    }  
    if(offset<memsize)//ƫ�����ڴ����. 
    {  
        int index=offset/memblksize;			//ƫ�������ڴ�����  
        int nmemb=mallco_dev.memmap[index];	//�ڴ������
        for(i=0;i<nmemb;i++)  						//�ڴ������
        {  
            mallco_dev.memmap[index+i]=0;  
        }  
        return 0;  
    }else return 2;//ƫ�Ƴ�����.  
}  
/*****************************���ϴ���Ƽ����޹�˾******************************
  * ��������	:myfree
  * ����˵��  :�ͷ��ڴ�(�ⲿ����)  
  * �������  :ptr�ڴ��׵�ַ                 
  * �������  : 
  * ���ز���  :
*******************************************************************************/
void myfree(void *ptr)  
{  
	u32 offset;  
    if(ptr==NULL)return;//��ַΪ0.  
 	offset=(u32)ptr-(u32)mallco_dev.membase;  
    mem_myfree(offset);//�ͷ��ڴ�     
}

/*****************************���ϴ���Ƽ����޹�˾******************************
  * ��������	:mymalloc
  * ����˵��  :�����ڴ�(�ⲿ����) 
  * �������  :size�ڴ��С(�ֽ�) 
                
  * �������  : 
  * ���ز���  :���䵽���ڴ��׵�ַ.
*******************************************************************************/
void *mymalloc(u32 size)  
{  
    u32 offset;  									      
	offset=mem_malloc(size);  	   				   
    if(offset==0XFFFFFFFF)return NULL;  
    else return (void*)((u32)mallco_dev.membase+offset);  
}  

/*****************************���ϴ���Ƽ����޹�˾******************************
  * ��������	:myrealloc
  * ����˵��  :���·����ڴ�(�ⲿ����) 
  * �������  :*ptr���ڴ��׵�ַ 
               size:Ҫ������ڴ��С(�ֽ�) 
  * �������  : 
  * ���ز���  :�·��䵽���ڴ��׵�ַ.
*******************************************************************************/
void *myrealloc(void *ptr,u32 size)  
{  
    u32 offset;  
    offset=mem_malloc(size);  
    if(offset==0XFFFFFFFF)return NULL;     
    else  
    {  									   
	    mymemcpy((void*)((u32)mallco_dev.membase+offset),ptr,size);	//�������ڴ����ݵ����ڴ�   
        myfree(ptr);  											  		//�ͷž��ڴ�
        return (void*)((u32)mallco_dev.membase+offset);  				//�������ڴ��׵�ַ
    }  
} 












