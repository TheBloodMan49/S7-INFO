import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LiseuseComponent } from './liseuse.component';

describe('LiseuseComponent', () => {
  let component: LiseuseComponent;
  let fixture: ComponentFixture<LiseuseComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [LiseuseComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(LiseuseComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
