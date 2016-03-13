#ifndef LOCK_H_
#define LOCK_H_

#include <unistd.h>
#include <fcntl.h>
#include <string>

class Lock {

private:
	struct flock fl;
	int fd;
	std::string nombre;
	bool liberado;

public:
	Lock ( const std::string nombre );
	~Lock();

	int tomarLock ();
	int liberarLock ();
	ssize_t escribir ( const void* buffser,const size_t buffsize ) const;
	ssize_t escribir ( const void* buffser,const size_t buffsize, int desde) const;
	int leer ();
};

#endif /* LOCK_H_ */
