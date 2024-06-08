cmake_minimum_required(VERSION 3.28)
project(sistema_registro_estudantes C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(sistema_registro_estudantes main.c
        src/app.c
        src/app.h
        src/infra/gtk/gtk.c
        src/infra/gtk/gtk.h
        src/infra/storage/storage.c
        src/infra/storage/storage.h
        src/modules/student/studentsModule.h
        src/modules/student/useCases/listStudents/listStudents.c
        src/modules/student/useCases/listStudents/listStudents.h
        src/modules/student/useCases/createStudent/createStudent.c
        src/modules/student/useCases/createStudent/createStudent.h
        src/modules/student/useCases/updateStudent/updateStudent.c
        src/modules/student/useCases/updateStudent/updateStudent.h
        src/modules/student/useCases/removeStudent/removeStudent.c
        src/modules/student/useCases/removeStudent/removeStudent.h
        src/modules/student/useCases/updateStudentList/updateStudentList.c
        src/modules/student/useCases/updateStudentList/updateStudentList.h
        src/modules/student/useCases/checkIfStudentExistsByCpf/checkIfStudentExistsByCpf.c
        src/modules/student/useCases/checkIfStudentExistsByCpf/checkIfStudentExistsByCpf.h
        src/modules/student/useCases/findStudent/findStudent.c
        src/modules/student/useCases/findStudent/findStudent.h
        src/modules/student/presentation/createStudentPresentation/createStudentPresentation.c
        src/modules/student/presentation/createStudentPresentation/createStudentPresentation.h
        src/modules/student/presentation/listStudentsPresentation/listStudentsPresentation.c
        src/modules/student/presentation/listStudentsPresentation/listStudentsPresentation.h
        src/modules/student/presentation/updateStudentPresentation/updateStudentPresentation.c
        src/modules/student/presentation/updateStudentPresentation/updateStudentPresentation.h
        src/modules/student/presentation/removeStudentPresentation/removeStudentPresentation.c
        src/modules/student/presentation/removeStudentPresentation/removeStudentPresentation.h
        src/modules/student/presentation/viewStudentPresentation/viewStudentPresentation.c
        src/modules/student/presentation/viewStudentPresentation/viewStudentPresentation.h
        src/modules/student/presentation/findStudentPresentation/findStudentPresentation.c
        src/modules/student/presentation/findStudentPresentation/findStudentPresentation.h
        src/infra/gtk/utils/alerts.c
        src/infra/gtk/utils/alerts.h
        src/shared/updateStudentId.c
        src/shared/updateStudentId.h
        src/shared/studentsFilePath.c
        src/shared/studentsFilePath.h
)

target_link_libraries(sistema_registro_estudantes ${GTK3_LIBRARIES})