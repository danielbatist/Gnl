/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:57:13 by dbatista          #+#    #+#             */
/*   Updated: 2024/10/22 10:15:10 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *rest_line; // armazena o que sobrou da ultima leitura,caso tenha sobrado algo.
	char	*line; // armazena a linha atual que está sendo lida.
	char	*buf; // vai ser alocado dinamicamente para receber os arquivos lidos.
	int		buf_read; // armazena os bytes lidos por read.
	
	if (!rest_line) // se o que sobrou da outra leitura for nulo ou se for a primeira leitura.
		rest_line = ft_strdup(""); // ela recebe uma string vazio, para inicializar.
	line = ft_strdup(rest_line); // line agora recebe uma duplicata do que estiver em rest_line.
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf_read = BUFFER_SIZE; // o buf_read aqui recebe BUFFER_SIZE, pois será a quantidade de bytes a serem lidos
	
	// a condição de loop se dá enquando o que eu vou ler for igual ao maximo que eu posso ler.
	// isso significa que, se meu buf_read for menor que BUFFER_SIZE, significa que estou perto do final do arquivo.
	// e a outra condição é ele continuar enquando não achamos um \n que siginifica que chegamos ao final da linha, se ele for <0 significa que não chegamos até o final de uma linha
	while (buf_read == BUFFER_SIZE && ft_line_break(line) < 0)
	{
		buf_read = read(fd, buf, BUFFER_SIZE); // read lê os dados do arquivos pelo fd que foi passado para get next line.
		// buf armazena o conteudo lido, pois ja foi alocado antes.
		// BUFFER_SIZE  o quanto será lido.
		// read retorna o valor de bytes lido, se for igual a BUFFER SIZE o loop continua, se for menor está perto do fim, se for 0 chegou ao fim do arquivo, se for -1 ocorreu algum erro.
		if (buf_read < 0) // se o valor retornado por read for menor que 0, ele libera a memoria que foi alocada até aqui.
			return (free_mem(&line, &rest_line, &buf));
		buf[buf_read] = '\0';
		line = ft_strjoin(line, buf); // chamamos a join para concatenar o string que existe em line, com a nova que a acabou de ser lida em buf, gerando uma nova string contendo o conteudo de line e buf juntas, join tera uma condição de liberar a memoria que antes line apontava e agora apontará para a nova string gerada.
	}
	return (ft_only_line(&rest_line, &buf, &line, buf_read)); // aqui faremos a extração completa da linha, até encontramos o \n se houver.
}