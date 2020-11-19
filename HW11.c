#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

int generate_rand() {
  int fd = open("/dev/random", O_RDONLY);
  if (fd == -1) {
    printf("Open failed: %s\n", strerror(errno));
  }
  int buffer;
  if (read(fd, &buffer, sizeof(buffer)) == -1) {
    printf("Read failed: %s\n", strerror(errno));
  }
  close(fd);
  return buffer;
}

int main() {
	int fd;

	int arr[10];
	int i;
	for (i = 0; i < 9; i++) {
		arr[i] = generate_rand();
		printf("%d, ", arr[i]);
	}
	printf("%d\n", arr[9]);

	fd = open("write_file", O_CREAT | O_RDWR, 0600);
	if (fd == -1) {
		printf("Open failed: %s\n", strerror(errno));
	}

	if (write(fd, arr, sizeof(arr)) == -1) {
		printf("Write failed: %s\n", strerror(errno));
	}
  close(fd);

  fd = open("write_file", O_RDONLY);
	int new_arr[10];
	if (read(fd, new_arr, sizeof(new_arr)) == -1) {
		printf("Read failed: %s\n", strerror(errno));
	}

	for (i = 0; i < 9; i++) {
		printf("%d, ", new_arr[i]);
	}
	printf("%d\n", new_arr[9]);
  
	close(fd);
	return 0;
}