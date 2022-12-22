QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    edit_widgets/audience_edit_widget.cpp \
    edit_widgets/group_edit_widget.cpp \
    edit_widgets/subject_edit_widget.cpp \
    edit_widgets/teacher_edit_widget.cpp \
    show_widgets/audience_widget.cpp \
    database.cpp \
    entries.cpp \
    show_widgets/entry_widget.cpp \
    show_widgets/group_widget.cpp \
    login_dialog.cpp \
    main.cpp \
    main_window.cpp \
    show_widgets/student_widget.cpp \
    show_widgets/subject_widget.cpp \
    show_widgets/teacher_widget.cpp \
    show_widgets/timetable_widget.cpp \
    edit_widgets/user_widget.cpp \
    edit_widgets/student_edit_widget.cpp \
    edit_widgets/timetable_edit_widget.cpp

HEADERS += \
    edit_widgets/audience_edit_widget.h \
    edit_widgets/group_edit_widget.h \
    edit_widgets/subject_edit_widget.h \
    edit_widgets/teacher_edit_widget.h \
    show_widgets/audience_widget.h \
    database.h \
    entries.h \
    show_widgets/entry_widget.h \
    show_widgets/group_widget.h \
    login_dialog.h \
    main_window.h \
    show_widgets/student_widget.h \
    show_widgets/subject_widget.h \
    show_widgets/teacher_widget.h \
    show_widgets/timetable_widget.h \
    edit_widgets/user_widget.h \
    edit_widgets/student_edit_widget.h \
    edit_widgets/timetable_edit_widget.h

FORMS += \
    edit_widgets/audience_edit_widget.ui \
    edit_widgets/group_edit_widget.ui \
    edit_widgets/subject_edit_widget.ui \
    edit_widgets/teacher_edit_widget.ui \
    show_widgets/audience_widget.ui \
    show_widgets/group_widget.ui \
    login_dialog.ui \
    main_window.ui \
    show_widgets/student_widget.ui \
    show_widgets/subject_widget.ui \
    show_widgets/teacher_widget.ui \
    show_widgets/timetable_widget.ui \
    edit_widgets/user_widget.ui \
    edit_widgets/student_edit_widget.ui \
    edit_widgets/timetable_edit_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resouces.qrc
