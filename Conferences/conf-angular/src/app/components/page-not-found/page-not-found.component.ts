import { HttpClient } from '@angular/common/http';
import { Component } from '@angular/core';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'app-page-not-found',
  standalone: true,
  imports: [RouterLink],
  templateUrl: './page-not-found.component.html',
  styleUrl: './page-not-found.component.css'
})
export class PageNotFoundComponent {
  image: string = "";

  constructor(private http: HttpClient) {}

  ngOnInit() {
    this.http.get("https://api.thecatapi.com/v1/images/search").subscribe((data: any) => {
      this.image = data[0].url;
    });
  }
}
