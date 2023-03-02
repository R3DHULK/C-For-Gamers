#include <stdio.h>

void move_disk(int n, char source, char dest, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", source, dest);
    } else {
        move_disk(n - 1, source, aux, dest);
        printf("Move disk %d from %c to %c\n", n, source, dest);
        move_disk(n - 1, aux, dest, source);
    }
}

int main() {
    int num_disks;
    printf("Enter the number of disks: ");
    scanf("%d", &num_disks);
    move_disk(num_disks, 'A', 'C', 'B');
    return 0;
}
