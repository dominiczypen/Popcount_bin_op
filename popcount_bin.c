#include <stdio.h>
unsigned char popcount(unsigned char a)
  // == Hamming weight == number of 1 in binary rep of a.
  // popcount(a ^ b) is Hamming distance of a,b
{
  unsigned char count = 0;
  while (a)
  {
    if (a & 1) { count++; } // increment count if rightmost bit == 1
    a = a >> 1;
  }
  return count;
}
// ----------------------------
void calc_popcounts_sum()
{
  unsigned int op_a_b_pop = 0;
  unsigned char a, b, outer_loop_started, inner_loop_started;
  a = 0;
  b = 0;
  outer_loop_started = 0; // == 0 before start of loop, 1 after
  inner_loop_started = 0;
  while ((a > 0) || (!outer_loop_started)) // use circularity: a \in [0,...,0xff]
  {
    outer_loop_started = 1;
    inner_loop_started = 0; // because of circularity issue
    while ((b > 0) || (!inner_loop_started))
    {
      inner_loop_started = 1;
      op_a_b_pop += popcount(a * b); 
             // --> instead of a * b, use +, &, ^, |, or any other binary op
      b++;
    }
    b = 0;
    a++;
  }
  printf("Total popcount for binary operation: %d\n", op_a_b_pop);
  int total_bits = (1 << 19); // (1 << 8) * (1 << 8) * (1 << 3) == (1 << (8+8+3))
  printf("Total bits: %d\n", total_bits);
  printf("Probability of occurrence of 1: 0.%d\n", 1000 * op_a_b_pop/total_bits);
}
// ----------------------------
int main()
{
  calc_popcounts_sum();
  return 0;
}
