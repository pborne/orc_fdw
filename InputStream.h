/*
 * InputStream.h
 *
 *  Created on: Aug 10, 2013
 *      Author: gokhan
 */

#ifndef INPUTSTREAM_H_
#define INPUTSTREAM_H_

#include <stdio.h>

typedef struct
{
	CompressionKind compressionKind;
	long compressionBlockSize;
} CompressionParameters;

extern CompressionParameters compressionParameters;

typedef struct
{
	/* Input stream for reading from the file */
	FILE* file;

	/* offset of the start of the buffer in the file */
	long offset;
	/* end of the file stream in the file */
	long limit;

	/* current position in the buffer */
	int position;
	/* current length of the buffer */
	int length;

	/* allocated buffer size */
	int bufferSize;
	/* buffer to store the file data */
	char* buffer;
} FileStream;

FileStream* FileStream_init(char* filePath, long offset, long limit, int bufferSize);
int FileStream_free(FileStream*);
char* FileStream_read(FileStream*, int *length);
int FileStream_skip(FileStream*, int skip);
long FileStream_bytesLeft(FileStream*);

typedef struct
{
	/* stream for decompression */
	FileStream* fileStream;

	/* block size used for compression */
	int bufferSize;
	CompressionKind compressionKind;

	/* current length in the uncompressed buffer */
	int position;
	/* current length of the uncompressed buffer */
	int length;
	/* buffer to store uncompressed data */
	char* uncompressedBuffer;
	/* true if uncompressed stream is the same as compressed one */
	char isOriginal;

	/* this is for reading bytes from cross boundries */
	char* tempBuffer;
} CompressedFileStream;

CompressedFileStream* CompressedFileStream_init(char* filePath, long offset, long limit, int bufferSize, CompressionKind kind);
int CompressedFileStream_free(CompressedFileStream*);
char* CompressedFileStream_read(CompressedFileStream*, int *length);
int CompressedFileStream_readByte(CompressedFileStream* stream, char* value);

#endif /* INPUTSTREAM_H_ */