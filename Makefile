# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lroux <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 14:23:48 by lroux             #+#    #+#              #
#    Updated: 2019/01/17 14:01:23 by lroux            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT	:= let-em-in
NAME	:= lem-in

SRCDIR	:= srcs
OBJDIR	:= objs
INCDIR	:= incs

SRCS	:= lemin.c collector.c \
		   parser/parser.c parser/parserooms.c parser/parsetubes.c

LIBS	:= libft libpf
LIBDIR	:= libs

# Include core
include $(LIBDIR)/project.mk


