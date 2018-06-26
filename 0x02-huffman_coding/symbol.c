#include "huffman.h"

/**
 * symbol_create - create a symbol struct
 *
 * @data: character found
 * @freq: frequency that character was seen
 *
 * Return: a new symbol struct pointer
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol;

	symbol = malloc(sizeof(symbol_t));
	if (symbol == NULL)
		return (NULL);
	symbol->data = data;
	symbol->freq = freq;
	return (symbol);
}
