import { Component, Input } from '@angular/core';
import { Planche } from '../../models/planche';
import { DatePipe } from '@angular/common';

@Component({
  selector: 'app-planche',
  standalone: true,
  imports: [DatePipe],
  templateUrl: './planche.component.html',
  styleUrl: './planche.component.css'
})
export class PlancheComponent {
  @Input() planche: Planche = new Planche();
}
