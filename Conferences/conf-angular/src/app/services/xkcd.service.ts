import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Planche } from '../models/planche';
import { map } from 'rxjs/operators';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class XkcdService {

  planches: Map<number, Planche> = new Map();

  constructor(private http: HttpClient) { }

  getPlancheNumero = (num: number): Observable<Planche> => {

    if (this.planches.has(num)) {
      return new Observable((observer) => {
        observer.next(this.planches.get(num));
        observer.complete();
      });
    }
    const answer = this.http.get(`/api/${num}/info.0.json`).pipe(map((planche: any) => new Planche(
      planche.num,
      planche.img,
      new Date(planche.year, planche.month, planche.day),
      planche.title
    )))

    answer.subscribe((planche) => {
      this.planches.set(planche.numero, planche);
    });

    return answer;
  } 
}
