project(GameLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h
        ids.h
        Item.cpp
        Item.h
        Game.cpp
        Game.h
        Scoreboard.cpp
        Scoreboard.h
        Level.cpp
        Level.h
        GameView.cpp
        GameView.h
        PlayingArea.cpp
        PlayingArea.h
        Declaration.cpp
        Declaration.h
        ItemSparty.cpp
        ItemSparty.h
        ItemXray.cpp
        ItemXray.h
        ItemNumber.cpp
        ItemNumber.h
        ItemGiven.cpp
        ItemGiven.h
        ItemDigit.cpp
        ItemDigit.h
        ItemContainer.cpp
        ItemContainer.h
        ItemBackground.cpp
        ItemBackground.h
        DeclarationNumber.cpp
        DeclarationNumber.h
        DeclarationGiven.cpp
        DeclarationGiven.h
        DeclarationDigit.cpp
        DeclarationDigit.h
        DeclarationBackground.cpp
        DeclarationBackground.h
        DeclarationContainer.cpp
        DeclarationContainer.h
        DeclarationSparty.cpp
        DeclarationSparty.h
        DeclarationXray.cpp
        DeclarationXray.h
        Vector.cpp
        Vector.h
        DeclarationVisitor.cpp
        DeclarationVisitor.h
        NumberDeclarationValueVisitor.cpp
        NumberDeclarationValueVisitor.h
        ItemVisitor.cpp
        ItemVisitor.h
        ItemTypeCounterVisitor.cpp
        ItemTypeCounterVisitor.h
        ItemWall.cpp
        ItemWall.h
        GetSpartyVisitor.cpp
        GetSpartyVisitor.h
        DeclarationWall.cpp
        DeclarationWall.h
        IsWallVisitor.cpp
        IsWallVisitor.h
        FindItemContainerVisitor.cpp
        FindItemContainerVisitor.h
        ItemDigitVisitor.cpp
        ItemDigitVisitor.h
        GetAllDigitsVisitor.cpp
        GetAllDigitsVisitor.h
        ItemNumberVisitor.cpp
        ItemNumberVisitor.h
        ErrorPopup.cpp
        ErrorPopup.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# Precomplied headers
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)