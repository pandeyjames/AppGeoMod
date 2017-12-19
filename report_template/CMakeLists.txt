cmake_minimum_required(VERSION 3.1)

# Set a project name an version number for our report
project(report VERSION 1.0)

# Helper function
function(COPY_FILES)
  foreach(NAME ${ARGN})
    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/${NAME} ${CMAKE_CURRENT_BINARY_DIR}/${NAME} COPYONLY )
  endforeach(NAME)
endfunction(COPY_FILES)

# Define latex compilers
set(LATEX_COMPILER pdflatex)
set(BIBTEX_COMPILER bibtex)



#####
# Set up a rule to compile our report

# List input content files
set( SRCS
  bibliography.bib
  dat/benchmark_vector_reserve.dat
  dat/benchmark_vector_stl.dat
  dat/benchmark_stl_sort.dat
  dat/benchmark_mylib_bubble.dat
  dat/benchmark_mylib_shell.dat
  gfx/lena.png
  gfx/first_demo.png
  gfx/manipulate.png
  gfx/zoom.png
  gfx/clearscreen.png
  gfx/insertsphere.png
  gfx/zoomout.png
  gfx/rotateobject.png
  gfx/movecamera.png
  gfx/rotate1.png
  gfx/rotate2.png
  gfx/flowchart.png
  gfx/select.png
  gfx/deleteobject.png
  gfx/modelcurve.png
  gfx/model.png

)
 
# Copy needed files
COPY_FILES(${SRCS})


# Add custom command
add_custom_command(
  OUTPUT    ${PROJECT_NAME}.pdf
  COMMAND   ${LATEX_COMPILER}   ARGS -output-directory=${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}
  COMMAND   ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_BINARY_DIR} ${BIBTEX_COMPILER} ${PROJECT_NAME}
  COMMAND   ${LATEX_COMPILER}   ARGS -output-directory=${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}
  COMMAND   ${LATEX_COMPILER}   ARGS -output-directory=${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}
  MAIN_DEPENDENCY ${PROJECT_NAME}.tex
  DEPENDS ${SRCS}
)

# Add custom target which "drive" the building and run the custom command (must depend on the custom command)
add_custom_target( ${PROJECT_NAME} ALL DEPENDS ${PROJECT_NAME}.pdf) 
