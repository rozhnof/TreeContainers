MAKEFLAGS += --no-print-directory -lpcre
CURRENT_DIR = $(shell pwd)

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
BROWSER_OPENER = @open
endif
ifeq ($(UNAME), Linux)
BROWSER_OPENER = @x-www-browser
endif
GNU_COMPILER = -D CMAKE_CXX_COMPILER=g++-13 -D CMAKE_C_COMPILER=gcc-13
.PHONY: clean tests gcov_report

THREADS = 4
CMAKE = cmake 

BUILD_DIR = ../build
DEBUG_DIR = ${BUILD_DIR}/debug
RELEASE_DIR = ${BUILD_DIR}/release

SOURCE_DIR = ./containers
LIB_DIR = containers
LIB_NAME = containers

TEST_DIR = ./containers/tests

PUURPLE = '\033[0;35m'
YELLOW = \033[1;33m
BLUE = '\033[1;36m'
GREEN='\033[0;32m'
LIGTH_GREEN='\033[1;32m'
RED='\033[0;31m'
NC=\033[0m

CODE_STYLE = google
UNAME := $(shell uname)

ifeq (UNAME, Darwin)
	LIB = ${LIB_NAME}.a
else
	LIB = lib${LIB_NAME}.a
endif

all: clean ${LIB} tests gcov_report


${LIB}: assemble_release



assemble_release: ${RELEASE_DIR}
	@echo
	@echo ${GREEN}"Building release ${YELLOW}${LIB}"${GREEN}"...${NC}"
	${CMAKE} -S ${SOURCE_DIR} -B ${RELEASE_DIR} -D CMAKE_BUILD_TYPE=Release ${GNU_COMPILER}
	${CMAKE} --build ${RELEASE_DIR}
	@echo ${LIGTH_GREEN}Successfully built "${YELLOW}${LIB}"${LIGTH_GREEN}"!${NC}"
	@echo

assemble_debug: ${DEBUG_DIR}
	@echo
	@echo ${GREEN}"Building debug ${YELLOW}${LIB}"${GREEN}"...${NC}"
	${CMAKE} -S ${SOURCE_DIR} -B ${DEBUG_DIR} -D CMAKE_BUILD_TYPE=Debug ${GNU_COMPILER}
	${CMAKE} --build ${DEBUG_DIR}
	@echo ${LIGTH_GREEN}Successfully built "${YELLOW}${LIB}"${LIGTH_GREEN}"!${NC}"
	@echo



${RELEASE_DIR}:
	@mkdir -p ${RELEASE_DIR}
${DEBUG_DIR}:
	@mkdir -p ${DEBUG_DIR}

.PHONY: tests
tests: assemble_release
	@echo
	@echo ${GREEN}"Testing...${NC}"
	@./${RELEASE_DIR}/tests/tests
	@echo ${LIGTH_GREEN}End!'${NC}'
	@echo


gcov_report: generate_report open_report

generate_report: assemble_debug
	@echo
	@echo ${GREEN}"Generating coverage report...${NC}"
	cmake --build ${DEBUG_DIR} --target tests_coverage
	@echo ${LIGTH_GREEN}Report was saved in "${YELLOW}${DEBUG_DIR}/tests/tests_coverage/index.html"${LIGTH_GREEN}"${NC}"
	@echo ${LIGTH_GREEN}End!'${NC}'
	@echo

open_report:
	@echo ${LIGTH_GREEN}Trying to open "${YELLOW}${DEBUG_DIR}/tests/tests_coverage/index.html"${LIGTH_GREEN}"...${NC}"
	@${BROWSER_OPENER} ${DEBUG_DIR}/tests/tests_coverage/index.html
	@echo ${LIGTH_GREEN}End!'${NC}'


clean:
	@echo
	@echo ${GREEN}"Cleaning...${NC}"
	@rm -rf *${BUILD_DIR}
	@rm -fr *.vscode
	@rm -fr *.log
	@rm -fr *.a
	@rm -fr *.h
	@rm -fr ../build/*
	@echo ${LIGTH_GREEN}End!'${NC}'
	@echo



SOURCES_CPP = $(shell find ${LIB_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.cc' -print)
HEADERS = $(shell find ${LIB_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

TEST_SOURCES = $(shell find ${TEST_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.cc' -print)
TEST_HEADERS = $(shell find ${TEST_DIR} -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)


.PHONY: prepare
prepare:clean style_correct files_and_dir_counter string_counter
	@echo ===============['${YELLOW}'STATUS'${NC}']===============
	@git status
	@echo =======================================

.PHONY:status
stat: files_and_dir_counter string_counter tests_counter

.PHONY: print_files
print_files:
	@echo ============['${YELLOW}'${LIB_NAME}'${NC}']=============
	@echo ${BLUE}"${HEADERS} ${SOURCES_CPP}'${NC}'"
	@echo ==========================================

.PHONY: style_check
style_check:
	@echo ${GREEN}"Check style...${NC}"
	@clang-format -n ${SOURCES_CPP} ${HEADERS} ${TEST_SOURCES} ${TEST_HEADERS}
	@echo ${LIGTH_GREEN}End!'${NC}'
	@echo

.PHONY: style_correct
style_correct:
	@echo ${GREEN}"Correct style...${NC}"
	@clang-format -i ${SOURCES_CPP} ${HEADERS} ${TEST_SOURCES} ${TEST_HEADERS}
	@echo ${LIGTH_GREEN}End!'${NC}'
	@echo

.PHONY: files_and_dir_counter
files_and_dir_counter:
	@echo "${YELLOW}"${LIB_NAME}"${NC}":
	@echo "	"Number of ${PUURPLE}files'${NC}':
	@echo 	"		"[${BLUE}${shell find  ${LIB_DIR} -type f -print | wc -l}'${NC}']
	@echo "	"Number of ${PUURPLE}directories'${NC}':
	@echo 	"		"[${BLUE}${shell find  ${LIB_DIR} -type d -print | wc -l}'${NC}']

.PHONY: string_counter
string_counter:
	@echo "${YELLOW}${LIB_NAME}${NC}:"
	@echo "	"Number of strings in ${PUURPLE}.h'${NC}' files:
	@echo 	"		"[${BLUE}${shell find ${LIB_DIR} -name '*.h' -type f -print0 | xargs -0 cat | wc -l}'${NC}']

.PHONY: string_counter
tests_counter:
	@echo "${YELLOW}${LIB_NAME} TESTS${NC}:"
	@echo "	"Number of strings in ${PUURPLE}.cc'${NC}' files:
	@echo 	"		"[${BLUE}${shell find ${TEST_DIR} -name '*.cc' -type f -print0 | xargs -0 cat | wc -l}'${NC}']
	@echo "	"Number of strings in ${PUURPLE}.h'${NC}' files:
	@echo 	"		"[${BLUE}${shell find ${TEST_DIR} -name '*.h' -type f -print0 | xargs -0 cat | wc -l}'${NC}']
