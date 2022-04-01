package org.example;

/**
 * Hello world!
 */
public class App {
  static {
    System.loadLibrary("native");
  }

  public static void main(String[] args) {
    final String result = new App().sayHello(args[0]);
    System.out.println("Result from C++ lib: " + result);
  }

  private native String sayHello(String name);
}
