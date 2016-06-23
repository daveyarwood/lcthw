#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lcthw/dbg.h>
#include <lcthw/ringbuffer.h>

RingBuffer* RingBuffer_create(int length) {
  RingBuffer* buffer = calloc(1, sizeof(RingBuffer));
  buffer->length = length + 1;
  buffer->start = 0;
  buffer->end = 0;
  buffer->buffer = calloc(buffer->length, 1);

  return buffer;
}

void RingBuffer_destroy(RingBuffer* buffer) {
  if (buffer) {
    free(buffer->buffer);
    free(buffer);
  }
}


