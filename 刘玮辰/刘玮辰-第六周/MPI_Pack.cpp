#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int buffer[100]; // ���ڴ洢����������
    int position = 0; // ��ǰλ��ָ��
    int i;

    // ��ʼ�� MPI ����
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // ���� 0 �������
        int data[] = {1, 2, 3};
        int count = sizeof(data) / sizeof(data[0]);

        // ʹ�� MPI_Pack �����ݴ���� buffer
        MPI_Pack(data, count, MPI_INT, buffer, 100, &position, MPI_COMM_WORLD);

        // ���ʹ��������ݵ����� 1
        MPI_Send(buffer, position, MPI_PACKED, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // ���� 1 ���մ���������
        MPI_Status status;
        MPI_Recv(buffer, 100, MPI_PACKED, 0, 0, MPI_COMM_WORLD, &status);

        // �������յ�������
        int received_data[3];
        int received_count = 3;
        position = 0;
        MPI_Unpack(buffer, 100, &position, received_data, received_count, MPI_INT, MPI_COMM_WORLD);

        // ��ӡ���յ�������
        for (i = 0; i < received_count; i++) {
            printf("Process %d received: %d\n", rank, received_data[i]);
        }
    }

    // ���� MPI ����
    MPI_Finalize();
    return 0;
}
