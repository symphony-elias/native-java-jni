# How to build
To generate the header file:
```
javac -h src/main/resources/native src/main/java/org/example/App.java
```

To compile and link the cpp file (on macOS)
```
cd ./src/main/resources/
g++ -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/darwin -I./native/org_example_App.h ./native/org_example_App.cpp -o Java_org_example_App_sayHello.o
g++ -dynamiclib -o libnative.dylib Java_org_example_App_sayHello.o -lc
```

# How to run after regular bytecode compilation
Add JVM option: `-Djava.library.path=./testJni/src/main/resources`

Add program argument: `"using JNI"`

# How to run using a native image
Install GraalVM and native-image:
```
sdk install java 22.0.0.2.r17-grl
sdk use java java 22.0.0.2.r17-grl
gu install native-image
```
After java bytecode compilation (e.g. thanks to IntelliJ or javac):
```
cd target/classes
native-image org.example.App
```
Execute:
```
./org.example.app "using JNI and a native executable"
```
