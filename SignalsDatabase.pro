QMAKE_CXX                       = @echo [C+] $@ && g++ 

QMAKE_CC                        = @echo [C+] $@ && gcc 

QMAKE_MOC                       = @echo [MO] $@ && moc 

QMAKE_LINK                      = @echo [LD] $@ && g++ 

QMAKE_RC                        = @echo [RC] $@ && windres 

#QMAKE_LFLAGS_WINDOWS            += -Wl,--subsystem,console -L../Trace/Client -LD:/usr/local/lib -L../Qxlnt/Qxlnt/release
QMAKE_LFLAGS_WINDOWS            += -mwindows -LD:/usr/local/lib -L../Qxlnt/Qxlnt/release

QMAKE_CXXFLAGS                  += -ID:/usr/local/include -I../Qxlnt/xlnt/include

RESOURCES                       += SignalsDB.qrc

QMAKE_LIBS                      = -lwsock32 -ltraceclient -lQxlnt

TARGET                          = SignalsDB

VERSION                         = "0.9.0"
QMAKE_TARGET_COMPANY            = "Vertiv"

QMAKE_TARGET_PRODUCT            = "Signals Database"

QMAKE_TARGET_COPYRIGHT          = "Copyright (C) 2023 Vertiv Company"

QT                              += core gui widgets

DEFINES                         += \

SOURCES                         += \
				   AlarmDisplayForm.cpp                         \
				   AlarmDisplayWindow.cpp                       \
				   AlarmInformation.cpp                         \
				   AlarmSignalPair.cpp                          \
				   ControlDisplayForm.cpp                       \
				   ControlDisplayWindow.cpp                     \
				   ControlInformation.cpp                       \
				   ControlSignalPair.cpp                        \
				   ElementDisplayLine.cpp                       \
				   ElementDisplayLineFormat.cpp                 \
				   EquipmentDisplayForm.cpp                     \
				   EquipmentDisplayWindow.cpp                   \
				   EquipmentInformation.cpp                     \
				   EquipmentSignalPair.cpp                      \
				   MainConfig.cpp                               \
				   MainDisplayWindow.cpp                        \
				   MainWindow.cpp                               \
				   NCUAlarmSignal.cpp                           \
				   NCUControlSignal.cpp                         \
				   NCUEquipment.cpp                             \
				   NCUEquipmentSet.cpp                          \
				   NCUSampleSignal.cpp                          \
				   NCUSettingSignal.cpp                         \
				   NCUSignal.cpp                                \
				   NavigationWindow.cpp                         \
				   SampleDisplayForm.cpp                        \
				   SampleDisplayWindow.cpp                      \
				   SampleInformation.cpp                        \
				   SampleSignalPair.cpp                         \
				   SettingDisplayForm.cpp                       \
				   SettingDisplayWindow.cpp                     \
				   SettingInformation.cpp                       \
				   SettingSignalPair.cpp                        \
				   SignalDisplayForm.cpp                        \
				   SignalDisplayWindow.cpp                      \
				   SignalStatsWindow.cpp                        \
				   SignalTabWindow.cpp                          \
				   SignalsInformation.cpp                       \
				   SystemConfig.cpp                             \
				   TrackNumber.cpp                              \
				   WindowHeader.cpp                             \
				   XCLOptions.cpp                               \
				   XMLCreateDialog.cpp                          \
				   main.cpp                                     \
				   sqlite3.c                                    \


HEADERS                         += \
				   AlarmDisplayForm.h                           \
				   AlarmDisplayWindow.h                         \
				   AlarmInformation.h                           \
				   AlarmSignalPair.h                            \
				   ControlDisplayForm.h                         \
				   ControlDisplayWindow.h                       \
				   ControlInformation.h                         \
				   ControlSignalPair.h                          \
				   ElementDisplayLine.h                         \
				   ElementDisplayLineFormat.h                   \
				   EquipmentDisplayForm.h                       \
				   EquipmentDisplayWindow.h                     \
				   EquipmentInformation.h                       \
				   EquipmentSignalPair.h                        \
				   MainConfig.h                                 \
				   MainDisplayWindow.h                          \
				   MainWindow.h                                 \
				   NCUAlarmSignal.h                             \
				   NCUControlSignal.h                           \
				   NCUEquipment.h                               \
				   NCUEquipmentSet.h                            \
				   NCUSampleSignal.h                            \
				   NCUSettingSignal.h                           \
				   NCUSignal.h                                  \
				   NavigationWindow.h                           \
				   SampleDisplayForm.h                          \
				   SampleDisplayWindow.h                        \
				   SampleInformation.h                          \
				   SampleSignalPair.h                           \
				   SettingDisplayForm.h                         \
				   SettingDisplayWindow.h                       \
				   SettingInformation.h                         \
				   SettingSignalPair.h                          \
				   SignalDisplayForm.h                          \
				   SignalDisplayWindow.h                        \
				   SignalStatsWindow.h                          \
				   SignalTabWindow.h                            \
				   SignalsInformation.h                         \
				   SystemConfig.h                               \
				   TrackNumber.h                                \
				   WindowHeader.h                               \
				   XCLOptions.h                                 \
				   XMLCreateDialog.h                            \
				   sqlite3.h                                    \

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
