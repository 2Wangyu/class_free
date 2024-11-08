

plugins {
    alias(libs.plugins.android.application)
}

android {
    namespace = "com.example.wifi_locate"
    compileSdk = 34



    defaultConfig {
        applicationId = "com.example.wifi_locate"
        minSdk = 31
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    buildToolsVersion = "34.0.0"

//    sourceSets {
//        main{
//            jniLibs.srcDirs = ['libs'];
//        }
//    }

}

dependencies {

    implementation(libs.appcompat)
    implementation(libs.material)
    implementation(libs.activity)
    implementation(libs.constraintlayout)
    implementation(libs.floatingactionbutton)







    testImplementation(libs.junit)
    androidTestImplementation(libs.ext.junit)


    androidTestImplementation(libs.espresso.core)
    implementation ("com.squareup.okhttp3","okhttp","4.12.0")

//    implementation("androidx.biometric:biometric:1.1.8")
//    implementation("androidx.biometric:biometric-ktx:1.2.0-alpha03")
//    implementation ("androidx.biometric:biometric:1.2.0-alpha04")
    implementation ("androidx.biometric:biometric:1.1.0")
    implementation ("com.alibaba.fastjson2",  "fastjson2","2.0.51")

}

