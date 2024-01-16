# [TARGET]
NAME				:=  philo

# [DEBUG OPTION]
DEBUG				:= -fsanitize=thread -g

# [COMPILATION FLAGS]
 CFLAGS				:=  -Wall -Wextra -Werror
#CFLAGS				:=  -Wall -Wextra -Werror $(DEBUG)

CC					:=  cc

# [MAINSTREAM DIR]
SRC_DIR         :=  ./srcs/
OBJS_DIR        :=  ./objs/
HEADER_DIR      :=  header

# [COLOR SETTINGS]
BLACK           :=  \033[0;30m
RED             :=  \033[0;31m
GREEN           :=  \033[0;32m
YELLOW          :=  \033[0;33m
BLUE            :=  \033[0;34m
PURPLE          :=  \033[0;35m
CYAN            :=  \033[0;36m
WHITE           :=  \033[0;37m
DEF_COLOR       :=  \033[0;39m
LF              :=  \e[1K\r

# # ================================== MANDATORY PART ====================================== #

###############################################################################################
############################### [MANDATORY directory] #########################################
###############################################################################################

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #
# [HEADER FILES]
HEADER_MANDATORY_DIR			:=  $(HEADER_DIR)/
HEADER_FILES_MANDATORY			:=  $(HEADER_MANDATORY_DIR)philosophers.h

# [MANDATORY DEFAULT DIRECTORIES]
MANDATORY						:= $(SRC_DIR)

# [MANDATORY DIRECTORIES]
# [MANDATORY SRCS FILE CLASS]
SRCS_MAIN						:=	$(addprefix $(MANDATORY), \
									main.c \
									utils.c \
									parsing.c \
									thread_monitor.c \
									thread_status.c)
 
# [AGGREGATION OF ALL MANDATORY CLASSES]
SRCS							:=	$(SRCS_MAIN)
						
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ #

# [MANDATORY OBJS DIRECTORY]
OBJS 				    		:= $(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

##############################################################################################
##############################################################################################
##############################################################################################

# [PROGRESS BAR SETTING]
# [FILE DATA]
TOTAL_FILES 	        		:= $(words $(SRCS))
CURRENT_FILE 		    		:= 1

# FOR EVAL
progress_bar	= 	printf "$(LF)$(RED)[ ♔Compiling...♔ ]$(DEF_COLOR) $(CYAN)[$(CURRENT_FILE)/$(TOTAL_FILES)]$(DEF_COLOR) [$(Yellow)%0.1f%%$(DEF_COLOR)] $(DEF_COLOR)\b" $$(echo "scale=1; ($(CURRENT_FILE) * 100) / $(TOTAL_FILES)" | bc); \
					printf "$(YELLOW)[%-*s%s]$(DEF_COLOR)" 38 "$$(printf '%0.*s' $$(($$(($(CURRENT_FILE) * 38)) / $(TOTAL_FILES))) '=========================================================================')>" ""; \
					printf "\n\033[2K$(DEF_COLOR)  ✔︎ $(CYAN)Compiling... $< $(DEF_COLOR) \033[A\033[999C\e[?25l\e[?25h"; \

# [MAKE ALL : MANDATORY RULE]
all: $(OBJS_DIR) $(NAME)

# [CREATING TARGET FILE + LIBFT ARCHIVE(libft.a)]
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\n"
	@echo "$(GREEN)===============================================$(DEF_COLOR)"
	@echo "$(GREEN)|     🥳  [$(NAME)] compile success. 🥳         |$(DEF_COLOR)"
	@echo "$(GREEN)===============================================$(DEF_COLOR)"

# [CREATING OBJECT FILES]
$(OBJS): objs/%.o: srcs/%.c $(HEADER_FILES_MANDATORY)
	@$(call progress_bar)
	@$(CC) $(CFLAGS) -I$(HEADER_MANDATORY_DIR) -c $< -o $@
	@$(eval CURRENT_FILE := $(shell expr $(CURRENT_FILE) + 1))
	
# [CREATING OBJECT DIRECTORY]
$(OBJS_DIR):
	@mkdir $(OBJS_DIR)

# # ====================================================================================================== #

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(OBJ_DIR_BONUS)
	@rm -rf $(LIB_DIR)/objs
	@rm -rf $(LIB)
	@printf "$(LF)🚧 $(Yellow)Cleaning...🚨 $(White) $(OBJ_BO) $(OBJ) \n$(DEF_COLOR)"
	@rm -rf $(OBJ_DIR)
	@printf "$(LF)$(YELLOW)Cleanup complete.$(DEFAULT_COLOR)\n\n"

fclean: clean
	@printf "$(LF)🚧 $(Red)Cleaning...🚨 $(White)$(NAME)\n"
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@rm -rf $(LIB_DIR)/objs
	@rm -rf $(LIB)
	@echo "$(RED)Executable removed.$(DEFAULT_COLOR)\n"
	@echo "$(CYAN)Clearing terminal in [3 seconds]...$(DEFAULT_COLOR)"	
	@clear

re: fclean
	@clear
	@printf "$(PURPLE) ♻️  REBUILD  ♻️\n\n$(DEF_COLOR)"
	@$(MAKE) all

.PHONY: all clean fclean re bonus
