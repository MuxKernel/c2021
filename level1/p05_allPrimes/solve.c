#include <stdio.h>
/*
打印2-1000以内的所有素数
打印出总的计算时间
尽可能优化算法的效率
*/
int method1( int m )
{
    // 从 2 ~ m-1 一个个试，如果有任一次除法取余不为0，那么不是素数
    for ( int i = m - 1; i > 1; i-- ) {
        if ( m % i != 0 ) {  // 取余不为0
            // printf( "%u不是素数", m );
            return 0;  // 不是素数
        }
    }
    // printf( "%u是素数", m );
    return 1;  //是素数
}

int main()
{

    for ( int i = 0; i < 1000; i++ ) {
        if ( method1( i ) ) {
            printf( "%d ", i );
        }
    }
}