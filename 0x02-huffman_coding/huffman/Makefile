
OUTPUT	=	huffman

OBJECTS	=	main.c \
			compress.c \
			decompress.c \
			../binary_tree_print.c \
			../heap/heap.h \
			../heap/binary_tree_node.c \
			../heap/heap_create.c \
			../heap/heap_delete.c \
			../heap/heap_extract.c \
			../heap/heap_insert.c \
			../heap/heap_ops.c \
			../huffman.h \
			../huffman_extract_and_insert.c \
			../huffman_priority_queue.c \
			../huffman_tree.c \
			../huffman_codes.c \
			../symbol.c \


$(OUTPUT) : $(OBJECTS)
			gcc -g3 -o $@ $^


.PHONEY :	clean

clean :
			rm -f $(OUTPUT)
