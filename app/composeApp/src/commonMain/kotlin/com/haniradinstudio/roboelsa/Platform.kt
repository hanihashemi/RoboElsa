package com.haniradinstudio.roboelsa

interface Platform {
    val name: String
}

expect fun getPlatform(): Platform