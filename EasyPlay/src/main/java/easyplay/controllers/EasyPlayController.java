package easyplay.controllers;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class EasyPlayController {

    @GetMapping("/")
    public String showJoystickPage() {
        return "home";
    }
}
