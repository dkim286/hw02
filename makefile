cc = gcc
sorting = sorting
pipe = time_pipe
shm = time_shm

# flags
librt = -lrt
pthread = -pthread

sorting: $(sorting).c
	@$(cc) $(pthread) $(sorting).c -o $(sorting)

pipe: $(pipe).c
	@$(cc) $(pipe).c -o $(pipe)

shm: $(shm).c
	@$(cc) $(shm).c -o $(shm) $(librt)

clean:
	@$(RM) $(sorting) $(pipe) $(shm) > /dev/null
