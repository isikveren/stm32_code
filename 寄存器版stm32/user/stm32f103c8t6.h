
void delay(int d)
{
    while (d--)
        ;
}

// 用来存放存放stm32寄存器映射代码

// 外设 perirheral

#define PERIRH_BASE ((unsigned int)0x40000000)
#define APB1PERIRH_BASE PERIRH_BASE
#define APB2PERIRH_BASE (PERIRH_BASE + 0X10000)
#define AHBPERIRH_BASE (PERIRH_BASE + 0X20000)

#define RCC_BASE (AHBPERIRH_BASE + 0X1000)
#define GPIOA_BASE (APB2PERIRH_BASE + 0X0800)
#define GPIOB_BASE (APB2PERIRH_BASE + 0X0C00)

// #define RCC_APB2ENR *(unsigned int *)(RCC_BASE + 0X018)

// #define GPIOB_CRL *(unsigned int *)(GPIOB_BASE + 0X00)
// #define GPIOB_CRH *(unsigned int *)(GPIOB_BASE + 0X04)
// #define GPIOB_IDR *(unsigned int *)(GPIOB_BASE + 0X08)
// #define GPIOB_ODR *(unsigned int *)(GPIOB_BASE + 0X0C)
// #define GPIOB_BSRR *(unsigned int *)(GPIOB_BASE + 0X10)
// #define GPIOB_BRR *(unsigned int *)(GPIOB_BASE + 0X14)
// #define GPIOB_LCKR *(unsigned int *)(GPIOB_BASE + 0X18)

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

typedef struct
{
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
} GPIO_TypeDef;

typedef struct
{
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t APB2RSTR;
    uint32_t APB1RSTR;
    uint32_t AHBENR;
    uint32_t APB2ENR;
    uint32_t APB1ENR;
    uint32_t BDCR;
    uint32_t CSR;
} RCC_TypeDef;

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define RCC ((RCC_TypeDef *)RCC_BASE)