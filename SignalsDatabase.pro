QMAKE_CXX                       = @echo [C+] $@ && g++ 

QMAKE_CC                        = @echo [C+] $@ && gcc 

QMAKE_MOC                       = @echo [MO] $@ && moc 

QMAKE_LINK                      = @echo [LD] $@ && g++ 

QMAKE_RC                        = @echo [RC] $@ && windres 

QMAKE_LFLAGS_WINDOWS            += -mwindows

QMAKE_CXXFLAGS                  += 

QMAKE_LIBS                      = 

TARGET                          = SignalsDB

VERSION                         = "0.0.0"
QMAKE_TARGET_COMPANY            = "Greg Saltis"

QMAKE_TARGET_PRODUCT            = "Signals Database"

QMAKE_TARGET_COPYRIGHT          = "Copyright (C) 2023 Greg Saltis"

QT                              += core gui widgets

DEFINES                         += \

SOURCES                         += \
				   AlarmDisplayWindow.cpp			\
				   ControlDisplayWindow.cpp			\
				   EquipmentDisplayWindow.cpp			\
				   MainDisplayWindow.cpp			\
				   MainWindow.cpp				\
				   NCUAlarmSignal.cpp				\
				   NCUControlSignal.cpp				\
				   NCUEquipment.cpp				\
				   NCUEquipmentSet.cpp				\
				   NCUSampleSignal.cpp				\
				   NCUSettingSignal.cpp				\
				   NCUSignal.cpp				\
				   SampleDisplayWindow.cpp			\
				   SettingDisplayWindow.cpp			\
				   SignalDisplayWindow.cpp			\
                                   SignalStatsWindow.cpp                        \
                                   SignalTabWindow.cpp                          \
				   SystemConfig.cpp				\
				   main.cpp					\
				   sqlite3.c					\


HEADERS                         += \
				   AlarmDisplayWindow.h				\
				   ControlDisplayWindow.h			\
				   EquipmentDisplayWindow.h			\
				   MainDisplayWindow.h				\
				   MainWindow.h					\
				   NCUAlarmSignal.h				\
				   NCUControlSignal.h				\
				   NCUEquipment.h				\
				   NCUEquipmentSet.h				\
				   NCUSampleSignal.h				\
				   NCUSettingSignal.h				\
				   NCUSignal.h					\
				   SampleDisplayWindow.h			\
				   SettingDisplayWindow.h			\
				   SignalDisplayWindow.h			\
                                   SignalStatsWindow.h                          \
                                   SignalTabWindow.h                            \
				   SystemConfig.h				\
				   sqlite3.h					\

FORMS                           += \

QMAKE_EXTRA_TARGETS             += junkclean
junkclean.target                = junkclean
junkclean.commands              = @echo Removing junk                           \
                                  && rm -rf $(wildcard core* *~)
junkclean.depends               = 

QMAKE_EXTRA_TARGETS             += cleanall
cleanall.target                 = cleanall
cleanall.commands               = 
cleanall.depends                = junkclean                                     \
                                  clean
