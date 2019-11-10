#include <__cross_studio_io.h>
#include <stm32f1xx.h>


void main(void)
{
while(1)
{
  RCC->APB2ENR |= (1<<2);
  // output mode is push pull 00
  GPIOA->CRL &= ~(1<<2);
  GPIOA->CRL &= ~(1<<3);
  GPIOA->CRL |= (1<<0)|(1<<1);
  // port output data register
  GPIOA->ODR |=  (1<< 0);
 } 
}