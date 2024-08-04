#include <stdio.h>

void TowerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) 
{
    if (n == 1) 
    {
        printf("Move disk 1 from %c to %c\n", from_rod, to_rod);
        return;
    }
    
    TowerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    printf("Move disk %d from %c to %c\n", n, from_rod, to_rod);
    TowerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() 
{
    int num_disks  = 0;
    
    printf("Enter the number of disks: ");
    scanf("%d", &num_disks);
    
    TowerOfHanoi(num_disks, 'A', 'C', 'B');
    
    return 0;
}