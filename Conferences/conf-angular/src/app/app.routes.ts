import { Routes } from '@angular/router';
import { LiseuseComponent } from './components/liseuse/liseuse.component';
import { PageNotFoundComponent } from './components/page-not-found/page-not-found.component';

export const routes: Routes = [
  {
    path: 'liseuse/:numero',
    component: LiseuseComponent,
    title: 'Liseuse'
  },
  {
    path: '404',
    component: PageNotFoundComponent,
    title: 'Not found'
  },
  {
    path: '',
    redirectTo: '/liseuse/2980',
    pathMatch: 'full'
  },
  {
    path: '**',
    redirectTo: '/404',
  }
];
