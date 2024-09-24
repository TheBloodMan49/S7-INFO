import { Component, Input } from '@angular/core';
import { PlancheComponent } from '../planche/planche.component';
import { Planche } from '../../models/planche';
import { XkcdService } from '../../services/xkcd.service';
import { ActivatedRoute, Router } from '@angular/router';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-liseuse',
  standalone: true,
  imports: [PlancheComponent, FormsModule],
  templateUrl: './liseuse.component.html',
  styleUrl: './liseuse.component.css'
})  
export class LiseuseComponent {
  numeroEnCours: number = 2980;
  plancheEnCours: Planche = new Planche();

  constructor(private xkcd: XkcdService, private route: ActivatedRoute, private router: Router) {}

  async ngOnInit() {
    this.route.params.subscribe(async params => {
      this.numeroEnCours = +params['numero'];
      this.plancheEnCours = await this.getPlancheNumero(this.numeroEnCours);
    });
  }

  async first() {
    this.numeroEnCours = 1;
    this.plancheEnCours = await this.getPlancheNumero(this.numeroEnCours);
    this.router.navigateByUrl(`/liseuse/${this.numeroEnCours}`);
  }

  async prev() {
    this.numeroEnCours = Math.max(1, this.numeroEnCours - 1);
    this.plancheEnCours = await this.getPlancheNumero(this.numeroEnCours);
    this.router.navigateByUrl(`/liseuse/${this.numeroEnCours}`);
  }

  async random() {
    this.numeroEnCours = Math.floor(Math.random() * 2980) + 1;
    this.plancheEnCours = await this.getPlancheNumero(this.numeroEnCours);
    this.router.navigateByUrl(`/liseuse/${this.numeroEnCours}`);
  }

  async next() {
    this.numeroEnCours = Math.min(2980, this.numeroEnCours + 1);
    this.plancheEnCours = await this.getPlancheNumero(this.numeroEnCours);
    this.router.navigateByUrl(`/liseuse/${this.numeroEnCours}`);
  }

  async last() {
    this.numeroEnCours = 2980;
    this.plancheEnCours = await this.getPlancheNumero(this.numeroEnCours);
    this.router.navigateByUrl(`/liseuse/${this.numeroEnCours}`);
  }

  async getPlancheNumero(num: number): Promise<Planche> {
    return new Promise((resolve, reject) => {
      this.xkcd.getPlancheNumero(num).subscribe(
        (planche: Planche) => {resolve(planche)},
        (error: any) => {reject(error)}
    );
    });
  }

  goTo() {
    if (this.numeroEnCours > 1 && this.numeroEnCours < 2980) {
      this.router.navigateByUrl(`/liseuse/${this.numeroEnCours}`);
    }
  }
}
