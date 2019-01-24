# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glodi <glodi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 14:23:48 by lroux             #+#    #+#              #
#    Updated: 2019/01/24 14:12:33 by glodi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT	:= let-em-in
NAME	:= lem-in

SRCDIR	:= srcs
OBJDIR	:= objs
INCDIR	:= incs

SRCS	:= lemin.c collector.c \
		   parser/parser.c parser/parserooms.c parser/parsetubes.c \
		   kraken/bfs.c kraken/q.c

LIBS	:= libft libpf
LIBDIR	:= libs

DEBUG	:= 1

# Include core
include $(LIBDIR)/project.mk
