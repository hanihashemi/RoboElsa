package com.haniradinstudio.roboelsa

import androidx.compose.ui.window.Window
import androidx.compose.ui.window.application

fun main() = application {
    Window(
        onCloseRequest = ::exitApplication,
        title = "Roboelsa",
    ) {
        App()
    }
}