import { Component } from '@angular/core';
import { RouterLink, RouterOutlet } from '@angular/router';
import { LiseuseComponent } from "./components/liseuse/liseuse.component";

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, LiseuseComponent, RouterLink],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
export class AppComponent {
  title = 'xkcd-reader';
}
