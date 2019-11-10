
#include <__cross_studio_io.h>
#include <stm32f1xx.h>

int k=0,p=0;
void main(void)
{
RCC->APB2ENR |= (1<<2);
  RCC->APB1ENR = (1 << 1);

  // output mode is push pull 00
  GPIOA->CRL &= ~(1<<2);
  GPIOA->CRL &= ~(1<<3);
  GPIOA->CRL |= (1<<0)|(1<<1);

  // to enable the Counter enable bit i.e CEN
  TIM3->CR1 = (1 << 0);
  //f = 8Mhz
  // t = 1/f = 1.25*10^-7  in one clock cycle.
  // N= 1/t = 8000000  number of clock cycles in 1 second.
  // p = 1024 prescaler value
  // N/P  = 8000000/1024 = 7812.5 = 1E84

  // TIMx->ARR max value of the count you want. ARR =  auto reload register.
  TIM3->ARR = 0x1E84;

  TIM3->PSC = 0x0400;

  //ARPE: Auto-reload preload enable
  //1: TIMx_ARR register is buffered.
  TIM3->CR1 |= (1 << 7);

  // Update interrupt enable.
  TIM3->DIER = (1 << 0);

  NVIC_EnableIRQ(TIM3_IRQn);
  // port output data register
  //GPIOA->ODR |=  (1<< 0);
  
  while (1) {
    //GPIOA->ODR |= (1 << 0);
    k++;
  }
 } 
void TIM3_IRQHandler(void) {

  if (TIM3->SR & 0x01) {
    TIM3->SR = ~(1 << 0);
    p++;
    GPIOA->ODR ^=  (1<< 0);
  }
}

