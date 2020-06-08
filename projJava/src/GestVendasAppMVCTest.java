import Controller.ControllerTest;
import Modelo.Model;
import View.ViewTest;

import java.io.IOException;

public class GestVendasAppMVCTest {

    public static void main(String[] args) throws ClassNotFoundException, IOException {

        ControllerTest c = new ControllerTest();
        ViewTest v = new ViewTest();
        Model m = new Model();
        c.interpretador(v, m);

    }
}
